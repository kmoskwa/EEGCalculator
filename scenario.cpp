#include "scenario.h"
#include <Windows.h>
#include <QCursor>
#include <QList>
#include <QMap>

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
    , m_xOffsetMultipilier(10)
    , m_yOffsetMultipilier(10)
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

    m_digitNeighbours[9].append(Neighbour(8,  0,  0));
    m_digitNeighbours[9].append(Neighbour(6,  0,  0));
    m_digitNeighbours[9].append(Neighbour(5,  0,  0));
    //qsrand(); 
    }
  ~scenarioPrivate(void) {}
  void randomizeEasySteps(int minRange = 5, int maxRange = 10)
    {
    m_easySteps = random(minRange, maxRange);
    }
  void randomizeDelay(int minRange = 1000, int maxRange = 10000)
    {
    m_delay = random(minRange, maxRange);
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

QList<int> scenario::geDigitSequence(void)
{
    return p->m_digitSequence;
    p->m_digitSequence.clear();
}

void scenario::onDigitClicked(int digit)
{
    p->m_digitSequence.clear();
    switch (p->m_currentScenario)
    {
        case 1:
        {
            if (true == p->nextStep())
            {
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
            // crash
            *((unsigned int*)0) = 0xDEAD;
            }
        }
        break;
        case 4:
        {
            if (true == p->nextStep())
            {
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
            if (true == p->nextStep())
            {
                p->m_digitSequence.append(p->random(0, 9));
                p->randomizeEasySteps();
                p->randomizeDelay();
            }
        }
        break;
        case 7:
        {
            // pressed digit replaced with another random neighbour digit, and coursor moved
            if (true == p->nextStep())
            {
                QCursor cursor;
                QPoint pos = cursor.pos();
                QPoint offset;
                offset.setX(20);
                offset.setY(20);
                pos += offset;
                cursor.setPos(pos);
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
        case 10:
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


QPointer<scenario> scenario::m_Instance;