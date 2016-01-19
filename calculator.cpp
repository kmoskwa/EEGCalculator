#include <scenario.h>

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include <math.h>

#include "button.h"
#include "calculator.h"

//! [0]
Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
//! [0]

//! [1]
    display = new QLineEdit("0");
//! [1] //! [2]
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 24);
    display->setFont(font);
//! [2]

//! [4]
    for (int i = 0; i < NumDigitButtons; ++i) {
	digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("\261"), SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("CE"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("C"), SLOT(clearAll()));

    Button *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    Button *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    Button *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    Button *divisionButton = createButton(tr("\367"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("\327"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *powerButton = createButton(tr("x\262"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));
//! [4]

//! [5]
    QGridLayout *mainLayout = new QGridLayout;
//! [5] //! [6]
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
#else
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
#endif
#if 1
    QToolButton *scenario = new QToolButton();
    m_scenarioButton = scenario;
    scenario->setPopupMode(QToolButton::ToolButtonPopupMode::MenuButtonPopup);
    scenario->setToolButtonStyle(Qt::ToolButtonTextOnly);
    scenario->setText("S00");
    scenario->setToolTip("Stimulation Scenario"); 
    QAction *s0 = new QAction("S00", scenario);
    connect(s0, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s0);
    QAction *s1 = new QAction("S01", scenario);
    connect(s1, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s1);
    QAction *s2 = new QAction("S02", scenario);
    connect(s2, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s2);
    QAction *s3 = new QAction("S03", scenario);
    connect(s3, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s3);
    QAction *s4 = new QAction("S04", scenario);
    connect(s4, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s4);
    QAction *s5 = new QAction("S05", scenario);
    connect(s5, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s5);
    QAction *s6 = new QAction("S06", scenario);
    connect(s6, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s6);
    QAction *s7 = new QAction("S07", scenario);
    connect(s7, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s7);
    QAction *s8 = new QAction("S08", scenario);
    connect(s8, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s8);
    QAction *s9 = new QAction("S09", scenario);
    connect(s9, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s9);
    QAction *s10 = new QAction("S10", scenario);
    connect(s10, SIGNAL(triggered(bool)), this, SLOT(slotScenarioActionTrigerred(bool)));
    scenario->addAction(s10);
    mainLayout->addWidget(scenario, 0, 0, 1, 1);
#endif
    mainLayout->addWidget(display, 0, 1, 1, 5);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("Hell's Calc"));
}
//! [6]

//! [7]
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    scenario::getInstance()->onDigitClicked(digitValue);

    if (display->text() == "0" && digitValue == 0.0)
        return;
    if (waitingForOperand) {
        display->clear();
	waitingForOperand = false;
    }
    QList<int> digitSequence = scenario::getInstance()->getDigitSequence();
    if (digitSequence.isEmpty())
      {
      digitSequence.append(digitValue);
      }
    while (false == digitSequence.isEmpty())
      {
      display->setText(display->text() + QString::number(digitSequence.takeFirst()));
      }
}
//! [7]

//! [8]
void Calculator::unaryOperatorClicked()
//! [8] //! [9]
{

    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        scenario::getInstance()->onButtonClicked("Sqrt");
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = sqrt(operand);
    } else if (clickedOperator == tr("x\262")) {
        scenario::getInstance()->onButtonClicked("x^2");
        result = pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        scenario::getInstance()->onButtonClicked("1/x");
        if (operand == 0.0) {
	    abortOperation();
	    return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
//! [9]

//! [10]
void Calculator::additiveOperatorClicked()
//! [10] //! [11]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    scenario::getInstance()->onButtonClicked(clickedOperator);

//! [11] //! [12]
    if (!pendingMultiplicativeOperator.isEmpty()) {
//! [12] //! [13]
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
	    return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

//! [13] //! [14]
    if (!pendingAdditiveOperator.isEmpty()) {
//! [14] //! [15]
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
	    return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

//! [15] //! [16]
    pendingAdditiveOperator = clickedOperator;
//! [16] //! [17]
    waitingForOperand = true;
}
//! [17]

//! [18]
void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    if (clickedOperator == "\367")
       {
       scenario::getInstance()->onButtonClicked("/");
       }
    else if (clickedOperator == "\327")
       {
       scenario::getInstance()->onButtonClicked("*");
       }

    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
	    return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}
//! [18]

//! [20]
void Calculator::equalClicked()
{
    scenario::getInstance()->onButtonClicked("=");

    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
	    return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
	    return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}
//! [20]

//! [22]
void Calculator::pointClicked()
{
    scenario::getInstance()->onButtonClicked(".");
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}
//! [22]

//! [24]
void Calculator::changeSignClicked()
{
    scenario::getInstance()->onButtonClicked("+/-");
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}
//! [24]

//! [26]
void Calculator::backspaceClicked()
{
    scenario::getInstance()->onButtonClicked("<<");
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}
//! [26]

//! [28]
void Calculator::clear()
{
    scenario::getInstance()->onButtonClicked("CE");
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}
//! [28]

//! [30]
void Calculator::clearAll()
{
    scenario::getInstance()->onButtonClicked("C");
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}
//! [30]

//! [32]
void Calculator::clearMemory()
{
    scenario::getInstance()->onButtonClicked("MC");
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    scenario::getInstance()->onButtonClicked("MR");
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    scenario::getInstance()->onButtonClicked("MS");
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    scenario::getInstance()->onButtonClicked("M+");
    equalClicked();
    sumInMemory += display->text().toDouble();
}
//! [32]
//! [34]
Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
//! [34]

//! [36]
void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}
//! [36]

//! [38]
bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\327")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\367")) {
	if (rightOperand == 0.0)
	    return false;
	factorSoFar /= rightOperand;
    }
    return true;
}
//! [38]

void Calculator::slotScenarioActionTrigerred(bool checked)
  {
  QObject *sender = QObject::sender();
  QPointer<QAction> action = qobject_cast<QAction *>(sender);
  if (false == action.isNull())
    {
    QString actionText = action->text();
    m_scenarioButton->setText(actionText);
    actionText = actionText.remove("S");
    int scenario = QVariant(actionText).toInt();
    scenario::getInstance()->setCurrentScenario(scenario);
    }
  int a = 0;
  }
