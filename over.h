#pragma once

#include <QDialog>

namespace Ui 
{
    class Over;
}

class Over : public QDialog
{
    Q_OBJECT
    
public:
    explicit Over(uint64_t score, QWidget *parent = nullptr);
    ~Over();
    
private slots:
    void on_but_quit_clicked();
    void on_but_newgame_clicked();
    
signals:
    void new_game();
private:
    Ui::Over *ui;
};
