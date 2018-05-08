#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionNew_Game_triggered();
private:
    Ui::MainWindow *ui;
    unsigned long long int score{};
    void keyPressEvent(QKeyEvent *);
    void create();
    void fill();
    void move_item(QTableWidgetItem *, const int, const int);
    bool move_items(const int);
    void merge_items(QTableWidgetItem *);
    void clear_item(QTableWidgetItem *);
    void check_color(QTableWidgetItem *);
    void check_over() const;
    bool empty_space(const int, const int) const;
    int get_data_item(const int, const int) const;
    QTableWidgetItem * get_curr_item(const int, const int) const;
    static const int size;
    bool finish{false};
};

#endif // MAINWINDOW_H
