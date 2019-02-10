#include "configurationdialog.h"
#include "ui_configurationdialog.h"

#include <qpushbutton.h>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);

    // signals for player name validation:
    connect(ui->player1Name,
            &QLineEdit::textChanged,
            this,
            &ConfigurationDialog::updateOKButtonState);
    connect(ui->player2Name,
            &QLineEdit::textChanged,
            this,
            &ConfigurationDialog::updateOKButtonState);
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::setPlayer1Name(const QString &p1name)
{
    ui->player1Name->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(const QString &p2name)
{
    ui->player2Name->setText(p2name);
}

void ConfigurationDialog::setPlayer1Type(const TicTacToeWidget::PlayerType &p1type)
{
    if(p1type == TicTacToeWidget::PlayerType::Human) {
        ui->p1Human->setChecked(true);
        ui->p1Computer->setChecked(false);
    } else
    if(p1type == TicTacToeWidget::PlayerType::Computer) {
        ui->p1Human->setChecked(false);
        ui->p1Computer->setChecked(true);
    }
}

void ConfigurationDialog::setPlayer2Type(const TicTacToeWidget::PlayerType &p2type)
{
    if(p2type == TicTacToeWidget::PlayerType::Human) {
        ui->p2Human->setChecked(true);
        ui->p2Computer->setChecked(false);
    } else
    if(p2type == TicTacToeWidget::PlayerType::Computer) {
        ui->p2Human->setChecked(false);
        ui->p2Computer->setChecked(true);
    }
}

QString ConfigurationDialog::player1Name() const
{
    return ui->player1Name->text();
}

QString ConfigurationDialog::player2Name() const
{
    return ui->player2Name->text();
}

TicTacToeWidget::PlayerType ConfigurationDialog::player1Type() const
{
    if(ui->p1Human->isChecked())
        return TicTacToeWidget::PlayerType::Human;
    else
        return TicTacToeWidget::PlayerType::Computer;
}

TicTacToeWidget::PlayerType ConfigurationDialog::player2Type() const
{
    if(ui->p2Human->isChecked())
        return TicTacToeWidget::PlayerType::Human;
    else
        return TicTacToeWidget::PlayerType::Computer;
}

void ConfigurationDialog::updateOKButtonState()
{
    QPushButton* okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    // we enable it only if both player names are not empty:
    okButton->setEnabled(!ui->player1Name->text().isEmpty()
                      && !ui->player2Name->text().isEmpty());
}
