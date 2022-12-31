#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include "calculator.h"
#include <QResizeEvent>

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < ui->calculatorLayout->count(); ++i)
    {
        QWidget* widget = ui->calculatorLayout->itemAt(i)->widget();
        QPushButton* button = qobject_cast<QPushButton*>( widget );

        if (button)
        {
            connect(button, SIGNAL(clicked()), this, SLOT(handleButtonClicked()));
        }
    }
}

CalculatorWindow::~CalculatorWindow()
{
    delete ui;
}

void CalculatorWindow::resizeEvent(QResizeEvent *e) {
    if (e->isAccepted()) {
        int newFontSize = e->size().height() / 20;
        if (newFontSize != currentFontSize) {
            currentFontSize = newFontSize;
            for (int i = 0; i < ui->calculatorLayout->count(); ++i)
            {
                QWidget* widget = ui->calculatorLayout->itemAt(i)->widget();
                QFont font = widget->font();
                font.setPointSize(currentFontSize);
                widget->setFont(font);
            }
        }
    }
}

void CalculatorWindow::handleButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>( sender() );
    QString buttonText = button->text();
    QLineEdit* lineEditResult = ui->lineEditResult;

    if(buttonText == "Del"){
        QString textDelete = lineEditResult->text();

        textDelete.chop(1);
        lineEditResult->setText(textDelete);
    }
    else if(buttonText == "C"){
        lineEditResult->setText("");
    }
    else if(buttonText == "="){
        try {
            double calculationResult;

            Calculator* calculator = CalculatorWindow::calculator;
            QString mathExpression = lineEditResult->text().trimmed();
            calculator->setExpression(mathExpression.toStdString());
            calculationResult = calculator->calculate();
            lineEditResult->setText(QString::number(calculationResult));
        } catch (...) {
            lineEditResult->setText("The expression is invalid");
        }
    }
    else {
        lineEditResult->insert(buttonText);
    }
}
