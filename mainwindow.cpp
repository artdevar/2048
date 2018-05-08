#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finish.h"
#include "over.h"
#include <QKeyEvent>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setDisabled(true);
    this->fill();
    this->create(); 
    this->create();
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    bool created = false;
    bool moved = false;
    bool merged = false;
    switch(event->key())
    {
    case Qt::Key_Down:
        {
            moved = this->move_items(event->key());
            for(int i = size - 1; i >= 0; --i)
            {
                for(int j = size - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(i > 0 && this->get_data_item(i, j) == this->get_data_item(i - 1, j))
                        {
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                            this->clear_item(this->get_curr_item(i - 1, j));
                        }
                    }
                }
            }
            this->move_items(event->key());
            break;
        }
    case Qt::Key_Up:
        {
            moved = this->move_items(event->key());
            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(i < size - 1 && this->get_data_item(i, j) == this->get_data_item(i + 1, j))
                        {
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                            this->clear_item(this->get_curr_item(i + 1, j));
                        }
                    }
                }
            }
            this->move_items(event->key());
            break;
        }
    case Qt::Key_Left:
        {
            moved = this->move_items(event->key());
            for(int i = 0; i < size; ++i)
            {
               for(int j = 0; j < size; ++j)
               {
                    if(!this->empty_space(i, j))
                    {
                        if(j < size - 1 && this->get_data_item(i, j) == this->get_data_item(i, j + 1))
                        {
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                            this->clear_item(this->get_curr_item(i, j + 1));
                        }
                    }
                }
            }
            this->move_items(event->key());
            break;
        }
    case Qt::Key_Right:
        {
            moved = this->move_items(event->key());
            for(int i = size - 1; i >= 0; --i)
            {
                for(int j = size - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(j > 0 && this->get_data_item(i, j) == this->get_data_item(i, j - 1))
                        {
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                            this->clear_item(this->get_curr_item(i, j - 1));
                        }
                    }
                }
            }
            this->move_items(event->key());
        }
    }
    if(moved || merged)
    {
        this->create();
        created = true;
    }
    if(merged) 
    {
        ui->statusBar->showMessage("Score: " + QString::number(score));
    }
    if(!created)
    {
        this->check_over();
    }
}

void MainWindow::create()
{
    srand(time(NULL));
    int x = rand() % size;
    int y = rand() % size;
    while(!this->empty_space(x, y))
    {
        x = rand() % size;
        y = rand() % size;
    }
    if(rand() % 100 >= 10)
    {
       this->get_curr_item(x,y)->setData(Qt::UserRole, 2);
    }
    else
    {
       this->get_curr_item(x,y)->setData(Qt::UserRole, 4);
    }
    this->check_color(this->get_curr_item(x, y));
    this->get_curr_item(x, y)->setText(ui->tableWidget->item(x,y)->data(Qt::UserRole).toString());
}

void MainWindow::on_actionNew_Game_triggered()
{
    ui->tableWidget->clear();
    this->statusBar()->clearMessage();
    this->score = 0;
    this->finish = false;
    this->fill();
    this->create();
    this->create();
}

void MainWindow::fill()
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setData(Qt::UserRole, 0);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void MainWindow::clear_item(QTableWidgetItem * item)
{
    item->setData(Qt::UserRole, 0);
    item->setText("");
    this->check_color(item);
}

void MainWindow::move_item(QTableWidgetItem * item, const int row, const int column)
{
    ui->tableWidget->item(row, column)->setData(Qt::UserRole, item->data(Qt::UserRole));
    ui->tableWidget->item(row, column)->setBackgroundColor(item->backgroundColor());
    ui->tableWidget->item(row, column)->setTextColor(item->textColor());
    ui->tableWidget->item(row, column)->setText(item->text());
}

bool MainWindow::move_items(const int event)
{
    bool moved = false;
    switch(event)
    {
    case Qt::Key_Down:
        {
            for(int i = size - 1; i >= 0; --i)
            {
                for(int j = size - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = size - 1;
                        while(pos >= 0 && !this->empty_space(pos, j)){--pos;}
                        if(pos <= -1 || pos <= i) continue;
                        this->move_item(this->get_curr_item(i, j), pos, j);
                        this->clear_item(this->get_curr_item(i, j));
                        moved = true;
                    }
                }
            }
            break;
        }
    case Qt::Key_Up:
        {
            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = 0;
                        while(pos < size && !this->empty_space(pos, j)){++pos;}
                        if(pos >= size || pos >= i) continue;
                        this->move_item(this->get_curr_item(i, j), pos, j);
                        this->clear_item(this->get_curr_item(i, j));
                        moved = true;
                    }
                }
            }
            break;
        }
    case Qt::Key_Left:
        {
            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = 0;
                        while(pos < size && !this->empty_space(i, pos)){++pos;}
                        if(pos >= size || pos >= j) continue;
                        this->move_item(this->get_curr_item(i, j), i, pos);
                        this->clear_item(this->get_curr_item(i, j));
                        moved = true;
                    }
                }
            }
            break;
        }
    case Qt::Key_Right:
        {
            for(int i = size - 1; i >= 0; --i)
            {
                for(int j = size - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = size - 1;
                        while(pos >= 0 && !this->empty_space(i, pos)){--pos;}
                        if(pos <= -1 || pos <= j) continue;
                        this->move_item(this->get_curr_item(i, j), i, pos);
                        this->clear_item(this->get_curr_item(i, j));
                        moved = true;
                    }
                }
            }
        }
    }
    return moved;
}

void MainWindow::check_color(QTableWidgetItem * item)
{
    int data_temp = item->data(Qt::UserRole).toInt();
    switch(data_temp)
    {
    case 0:
        {
            item->setBackgroundColor((QColor(204,192,179)));
            return;
        }
    case 2:
        {
            item->setBackgroundColor((QColor(238,226,214)));
            item->setTextColor(QColor(50,50,50));
            return;
        }
    case 4:
        {
            item->setBackgroundColor(QColor(239,222,194));
            item->setTextColor(QColor(50,50,50));
            return;
        }
    }
    item->setTextColor(QColor(230,230,230));
    switch(data_temp)
    {
    case 8:
        {
            item->setBackgroundColor(QColor(248, 175, 106));
            break;
        }
    case 16:
        {
            item->setBackgroundColor(QColor(253, 145, 81));
            break;
        }
    case 32:
        {
            item->setBackgroundColor(QColor(254, 123, 77));
            break;
        }
    case 64:
        {
            item->setBackgroundColor(QColor(205, 65, 5));
            break;
        }
    case 128:
        {
            item->setBackgroundColor(QColor(242, 204, 102));
            item->setFont(QFont("Clear Sans", 27));
            break;
        }
    case 256:
        {
            item->setBackgroundColor(QColor(240, 195, 78));
            item->setFont(QFont("Clear Sans", 27));
            break;
        }
    case 512:
        {
            item->setBackgroundColor(QColor(242, 192, 61));
            item->setFont(QFont("Clear Sans", 27));
            break;
        }
    case 1024:
        {
            item->setBackgroundColor(QColor(242, 189, 51));
            item->setFont(QFont("Clear Sans", 25));
            break;
        }
    case 2048:
        {
            item->setBackgroundColor(QColor(242, 182, 49));
            item->setFont(QFont("Clear Sans", 25));
            if(!finish)
            {
                finish = true;
                Finish * window = new Finish(QString::number(score));
                window->show();
                connect(window, SIGNAL(new_game()), this, SLOT(on_actionNew_Game_triggered()));
            }
            break;
        }
    default:
    {
        item->setBackgroundColor(QColor(41, 39, 27));
        item->setFont(QFont("Clear Sans", 20));
    }
    }
}

void MainWindow::merge_items(QTableWidgetItem * res)
{
    res->setData(Qt::UserRole, res->data(Qt::UserRole).toInt() * 2);
    res->setText(res->data(Qt::UserRole).toString());
    this->check_color(res);
    score += res->data(Qt::UserRole).toInt();
}

void MainWindow::check_over() const
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(this->empty_space(i, j))
            {
                return;
            }
        }
    }
    for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                int temp_data = this->get_data_item(i, j);
                if(i < size - 2 && temp_data == this->get_data_item(i + 1, j))
                {
                    return;
                }
                if(i > 0 && temp_data == this->get_data_item(i - 1, j))
                {
                    return;
                }
                if(j < size - 2 && temp_data == this->get_data_item(i, j + 1))
                {
                    return;
                }
                if(j > 0 && temp_data == this->get_data_item(i, j - 1))
                {
                    return;
                }
            }
        }
    ui->tableWidget->setDisabled(true);
    Over * window = new Over(QString::number(score));
    window->show();
    connect(window, SIGNAL(new_game()), this, SLOT(on_actionNew_Game_triggered()));
}

bool MainWindow::empty_space(const int x, const int y) const
{
   return ui->tableWidget->item(x, y)->data(Qt::UserRole).toInt() == 0;
}

int MainWindow::get_data_item(const int x, const int y) const
{
    return ui->tableWidget->item(x, y)->data(Qt::UserRole).toInt();
}

QTableWidgetItem * MainWindow::get_curr_item(const int x, const int y) const
{
    return ui->tableWidget->item(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const int MainWindow::size = 4;