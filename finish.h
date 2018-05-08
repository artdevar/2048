#ifndef FINISH_H
#define FINISH_H

#include <QDialog>

namespace Ui {
class Finish;
}

class Finish : public QDialog
{
    Q_OBJECT
    
public:
    explicit Finish(const QString & str, QWidget *parent = 0);
    ~Finish();
    
private slots:
    void on_but_quit_clicked();
    void on_but_continue_clicked();
    void on_but_newgame_clicked();
signals:
    void new_game();
private:
    Ui::Finish *ui;
};

#endif // FINISH_H
