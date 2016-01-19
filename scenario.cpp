#include "scenario.h"
#include <Windows.h>
#include <QCursor>
#include <QList>
#include <QMap>
#include <QPointer>
#include <QTime>
#include <QVariant>
#include <EEGOpenVibe.h>
#include <fstream>

class EEGLogger
  {
  public:
  void log(QString text)
    {
    log(0, text);
    }
  void log(int stimulationNumber, QString text)
    {
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("yyyy.MM.dd;hh:mm:ss.zzz");
    QString message = timeStr + ";" + QVariant(stimulationNumber).toString() + ";" + text;
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app);
    outfile << message.toLocal8Bit().data() << std::endl; 
    // outfile.close(); // no need to close manually as its done during destruction
    }
  };

class scenarioPrivate
{
public:
  class Neighbour
    {
    public:
    Neighbour(int digit, int xOffset, int yOffset) : m_digit(digit), m_xOffset(xOffset), m_yOffset(yOffset) {}
    int m_digit;
    int m_xOffset;
    int m_yOffset;
    };

  scenarioPrivate(void) 
    : m_currentScenario(0)
    , m_easySteps(6)
    , m_delay(0)
    , m_xOffsetMultipilier(80)
    , m_yOffsetMultipilier(45)
    {
    m_digitNeighbours[1].append(Neighbour(2, 1, 0));
    m_digitNeighbours[1].append(Neighbour(4,  0, -1));
    m_digitNeighbours[1].append(Neighbour(5,  1, -1));

    m_digitNeighbours[2].append(Neighbour(1, -1,  0));
    m_digitNeighbours[2].append(Neighbour(3,  1,  0));
    m_digitNeighbours[2].append(Neighbour(4, -1, -1));
    m_digitNeighbours[2].append(Neighbour(5,  0, -1));
    m_digitNeighbours[2].append(Neighbour(6,  1, -1));

    m_digitNeighbours[3].append(Neighbour(2, -1,  0));
    m_digitNeighbours[3].append(Neighbour(6,  0, -1));
    m_digitNeighbours[3].append(Neighbour(5, -1, -1));

    m_digitNeighbours[4].append(Neighbour(1,  0,  1));
    m_digitNeighbours[4].append(Neighbour(5,  1,  0));
    m_digitNeighbours[4].append(Neighbour(7,  0, -1));
    m_digitNeighbours[4].append(Neighbour(8,  1, -1));
    m_digitNeighbours[4].append(Neighbour(2,  1,  1));

    m_digitNeighbours[5].append(Neighbour(2,  0, -1));
    m_digitNeighbours[5].append(Neighbour(6,  1,  0));
    m_digitNeighbours[5].append(Neighbour(4, -1,  0));
    m_digitNeighbours[5].append(Neighbour(8,  0, -1));
    m_digitNeighbours[5].append(Neighbour(1, -1,  1));
    m_digitNeighbours[5].append(Neighbour(3,  1,  1));
    m_digitNeighbours[5].append(Neighbour(9,  1, -1));
    m_digitNeighbours[5].append(Neighbour(7, -1, -1));

    m_digitNeighbours[6].append(Neighbour(5, -1,  0));
    m_digitNeighbours[6].append(Neighbour(9,  0, -1));
    m_digitNeighbours[6].append(Neighbour(3,  0,  1));
    m_digitNeighbours[6].append(Neighbour(2, -1,  1));
    m_digitNeighbours[6].append(Neighbour(8, -1, -1));

    m_digitNeighbours[7].append(Neighbour(4,  0,  1));
    m_digitNeighbours[7].append(Neighbour(8,  1,  0));
    m_digitNeighbours[7].append(Neighbour(5,  1,  1));

    m_digitNeighbours[8].append(Neighbour(7, -1,  0));
    m_digitNeighbours[8].append(Neighbour(5,  0,  1));
    m_digitNeighbours[8].append(Neighbour(9,  1,  0));
    m_digitNeighbours[8].append(Neighbour(4, -1,  1));
    m_digitNeighbours[8].append(Neighbour(6,  1,  1));

    m_digitNeighbours[9].append(Neighbour(8, -1,  0));
    m_digitNeighbours[9].append(Neighbour(6,  0,  1));
    m_digitNeighbours[9].append(Neighbour(5, -1,  1));

    m_openVibe = EEGOpenVibe::getInstance();
    m_log.log("start");
    //qsrand(); 
    }

  ~scenarioPrivate(void)
    {
    m_log.log("finish");
    }

  void randomizeEasySteps(int minRange = 5, int maxRange = 10)
    {
    m_easySteps = random(minRange, maxRange);
    }

  void randomizeDelay(int minRange = 1000, int maxRange = 10000)
    {
    m_delay = random(minRange, maxRange);
    }

  bool nextStepPeek(void)
    {
    return m_easySteps <= 1 ? true : false;
    }

  bool nextStep(void)
    {
    m_easySteps--;
    if (m_easySteps <= 0)
      {
      return true;
      }
    return false;
    }
  int random(int minRange, int maxRange)
    {
    return (minRange + qrand() * (maxRange - minRange) / RAND_MAX);
    }

  int m_easySteps;
  int m_delay;
  int m_currentScenario;
  int m_xOffsetMultipilier;
  int m_yOffsetMultipilier;
  QList<int> m_digitSequence;
  QMap<int, QList<Neighbour> > m_digitNeighbours;
  QPointer<EEGOpenVibe> m_openVibe;
  EEGLogger m_log;
};

scenario* scenario::getInstance(void)
  {
  if (m_Instance.isNull())
    {
    m_Instance = new scenario();
    }
  return m_Instance;
  }
 

scenario::scenario(QObject *parent)
  : QObject(parent)
{
    p = new scenarioPrivate();
    connect(p->m_openVibe, SIGNAL(signalStimulationSent    (int, int) ),
            this,         SLOT(  slotStimulationReceived(int, int) ),
            Qt::QueuedConnection);
}

scenario::~scenario()
{
    delete p;
}

int scenario::getCurrentScenario()
{
    return p->m_currentScenario;
}
void scenario::setCurrentScenario(int currentScenario)
{
    p->m_currentScenario = currentScenario;
}

QList<int> scenario::getDigitSequence(void)
{
    return p->m_digitSequence;
    p->m_digitSequence.clear();
}

void scenario::onButtonClicked(const QString &aButton)
{
    p->m_log.log(QString("onButtonClicked(%1)").arg(aButton));
}

void scenario::onDigitClicked(int digit)
{
    p->m_log.log(QString("onDigitClicked(%1)").arg(digit));
    p->m_digitSequence.clear();
    //if (true == p->nextStepPeek())
      {
      //p->m_openVibe->slotSimulationReceived("test", p->m_currentScenario, 1);
      p->m_openVibe->slotSimulationReceived("calculator", digit);
      }
    switch (p->m_currentScenario)
    {
        case 1:
        {
            if (true == p->nextStep())
            {
                p->m_log.log(1, QString("ERR stimulation;sleep(%1)").arg(p->m_delay));
                Sleep(p->m_delay);
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 2:
        {
            if (true == p->nextStep())
            {
                p->m_log.log(2, QString("ERR stimulation;mouseFreeze(%2)").arg(p->m_delay));
                QCursor cursor;
                QPoint currentPos = cursor.pos();
                int i = p->m_delay * 500;
                for(i; i >=0; i--)
                  {
                  //Sleep(1);
                  cursor.setPos(currentPos);
                  }
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 3:
        {
            if (true == p->nextStep())
            {
                p->m_log.log(3, QString("ERR stimulation;crash"));
                // crash
                *((unsigned int*)0) = 0xDEAD;
            }
        }
        break;
        case 4:
        {
            if (true == p->nextStep())
            {
                p->m_log.log(4, QString("ERR stimulation;exit"));
                // quick exit
                exit(1);
            }
        }
        break;
        case 5:
        {
            // pressed digit replaced with two the same digits
            if (true == p->nextStep())
            {
                p->m_log.log(5, QString("ERR stimulation;newDigit(%1)+doubled").arg(digit));
                p->m_digitSequence.append(digit);
                p->m_digitSequence.append(digit);
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 6:
        {
            // pressed digit replaced with another random neighbour digit 
            //QList<scenarioPrivate::Neighbour>::const_iterator iB = p->m_digitNeighbours[digit].begin();
            //QList<scenarioPrivate::Neighbour>::const_iterator iE = p->m_digitNeighbours[digit].begin();
            if (true == p->nextStep())
            {
                int count = p->m_digitNeighbours[digit].count(); 
                int idx = p->random(0, count);
                int newDigit = p->m_digitNeighbours[digit][idx].m_digit;
                p->m_log.log(6, QString("ERR stimulation;newDigit(%1)").arg(newDigit));
                p->m_digitSequence.append(newDigit);
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 7:
        {
            // pressed digit replaced with another random neighbour digit 
            //QList<scenarioPrivate::Neighbour>::const_iterator iB = p->m_digitNeighbours[digit].begin();
            //QList<scenarioPrivate::Neighbour>::const_iterator iE = p->m_digitNeighbours[digit].begin();
            if (true == p->nextStep())
            {
                int newDigit = p->random(0, 9);
                p->m_log.log(7, QString("ERR stimulation;newDigit(%1)").arg(newDigit));
                p->m_digitSequence.append(newDigit);
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 10:
        {
            // pressed digit replaced with another random neighbour digit, and coursor moved
            if (true == p->nextStep())
            {
                p->m_log.log(10, QString("ERR stimulation").arg(digit));
                int count = p->m_digitNeighbours[digit].count(); 
                int idx = p->random(0, count);
                int newDigit = p->m_digitNeighbours[digit][idx].m_digit;
                int xOffset = p->m_digitNeighbours[digit][idx].m_xOffset * p->m_xOffsetMultipilier;
                int yOffset = p->m_digitNeighbours[digit][idx].m_yOffset * p->m_yOffsetMultipilier;
                QCursor cursor;
                QPoint pos = cursor.pos();
                QPoint offset;
                offset.setX(xOffset);
                offset.setY(yOffset);
                pos += offset;
                cursor.setPos(pos);
                p->m_digitSequence.append(newDigit);
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 8:
        {
            if (true == p->nextStep())
            {
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 9:
        {
            if (true == p->nextStep())
            {
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        default:
        {
        // intentional
        }
    }
}

void scenario::slotStimulationReceived(int button, int isOn)
  {
  if (0 == button)
    {
    if (1 == isOn)
      {
      //slotStartButtonClicked();
      }
    else
      {
      //slotStopButtonClicked();
      }
    }
  }


QPointer<scenario> scenario::m_Instance;