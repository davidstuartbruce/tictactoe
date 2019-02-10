#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include "tictactoewidget.h"

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();
    void setPlayer1Name(const QString &p1name);
    void setPlayer2Name(const QString &p2name);
    void setPlayer1Type(const TicTacToeWidget::PlayerType &p1type);
    void setPlayer2Type(const TicTacToeWidget::PlayerType &p2type);

    QString player1Name() const;
    QString player2Name() const;
    TicTacToeWidget::PlayerType player1Type() const;
    TicTacToeWidget::PlayerType player2Type() const;

private:
    Ui::ConfigurationDialog *ui;
private slots:
    void updateOKButtonState();
};

#endif // CONFIGURATIONDIALOG_H
