#pragma once

#include "ui_mainwindow.h"
#include "finish.h"
#include "over.h"
#include <QMainWindow>
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
    
    static const int SIZE = 4;
    
    bool finish = false;
    uint64_t score = 0UL;
    
    mutable uint64_t record;
    
    const QString RECORD_FILE_NAME = "data_record.dat";
    
// Private functions
    
    // catches key pressing
    virtual void keyPressEvent(QKeyEvent *) override;
    // cathes closing window
    virtual void closeEvent(QCloseEvent *) override;
    
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
    
    void read_record() const;
    void write_record() const;
    
    void update_status_bar() const;
};
