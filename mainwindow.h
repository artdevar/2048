#pragma once

#include "ui_mainwindow.h"
#include "finish.h"
#include "over.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QKeyEvent>

namespace Ui 
{
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
    
    void keyPressEvent(QKeyEvent *);
    void create();
    void fill();
    void move_item(QTableWidgetItem *, const int, const int);
    bool move_items(const int);
    void merge_items(QTableWidgetItem *);
    void clear_item(QTableWidgetItem *);
    void check_color(QTableWidgetItem *);
    void show_best_score() const;
    void update_best_score() const;
    void check_over() const;
    bool empty_space(const int, const int) const;
    int get_data_item(const int, const int) const;
    QTableWidgetItem * get_curr_item(const int, const int) const;
    static const int size;
    bool finish{false};
    unsigned long long int score{};
};
