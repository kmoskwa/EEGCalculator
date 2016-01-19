#ifndef SCENARIO_H
#define SCENARIO_H

#include <QObject>
#include <QPointer>
 
class scenarioPrivate;

class scenario : public QObject
{
  Q_OBJECT

public:
    static scenario* getInstance(void);

    int getCurrentScenario();
    void setCurrentScenario(int currentScenario);

    void onDigitClicked(int digit);
    void onButtonClicked(const QString &aButton);
    QList<int> getDigitSequence(void);

    void slotStimulationReceived(int button, int isOn);

private:
    scenario(QObject *parent = NULL);
    ~scenario();

    scenarioPrivate *p;

    static QPointer<scenario> m_Instance;
};

#endif // SCENARIO_H
