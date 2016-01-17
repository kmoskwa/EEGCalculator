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
    QList<int> geDigitSequence(void);

private:
    scenario(QObject *parent = NULL);
    ~scenario();

    scenarioPrivate *p;

    static QPointer<scenario> m_Instance;
};

#endif // SCENARIO_H
