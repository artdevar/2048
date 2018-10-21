#include "mainwindow.h"
#include <QFile>
#include <QDataStream>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setDisabled(true);
    this->read_record();
    this->on_actionNew_Game_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    bool created = false;
    bool merged = false;
    bool moved = this->move_items(event->key());
    switch(event->key())
    {
    case Qt::Key_Down:
        {
            for(int i = SIZE - 1; i >= 0; --i)
            {
                for(int j = SIZE - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(i > 0 && this->get_data_item(i, j) == this->get_data_item(i - 1, j))
                        {
                            this->clear_item(this->get_curr_item(i - 1, j));
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                        }
                    }
                }
            }
            break;
        }
    case Qt::Key_Up:
        {
            for(int i = 0; i < SIZE; ++i)
            {
                for(int j = 0; j < SIZE; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(i < SIZE - 1 && this->get_data_item(i, j) == this->get_data_item(i + 1, j))
                        {
                            this->clear_item(this->get_curr_item(i + 1, j));
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                        }
                    }
                }
            }
            break;
        }
    case Qt::Key_Left:
        {
            for(int i = 0; i < SIZE; ++i)
            {
               for(int j = 0; j < SIZE; ++j)
               {
                    if(!this->empty_space(i, j))
                    {
                        if(j < SIZE - 1 && this->get_data_item(i, j) == this->get_data_item(i, j + 1))
                        {
                            this->clear_item(this->get_curr_item(i, j + 1));
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                        }
                    }
                }
            }
            break;
        }
    case Qt::Key_Right:
        {
            for(int i = SIZE - 1; i >= 0; --i)
            {
                for(int j = SIZE - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        if(j > 0 && this->get_data_item(i, j) == this->get_data_item(i, j - 1))
                        {
                            this->clear_item(this->get_curr_item(i, j - 1));
                            this->merge_items(this->get_curr_item(i, j));
                            merged = true;
                        }
                    }
                }
            }
        }
    }
    this->move_items(event->key());

    if(merged || moved) 
    {
        this->create();
        created = true;
    }

    if(!created)
    {
        this->check_over();
    }
}

bool MainWindow::move_items(const int event)
{
    bool moved = false;
    switch(event)
    {
    case Qt::Key_Down:
        {
            for(int i = SIZE - 1; i >= 0; --i)
            {
                for(int j = SIZE - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = SIZE - 1;
                        while(pos >= 0 && !this->empty_space(pos, j)){--pos;}
                        if(pos <= i) continue;
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
            for(int i = 0; i < SIZE; ++i)
            {
                for(int j = 0; j < SIZE; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = 0;
                        while(pos < SIZE && !this->empty_space(pos, j)){++pos;}
                        if(pos >= i) continue;
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
            for(int i = 0; i < SIZE; ++i)
            {
                for(int j = 0; j < SIZE; ++j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = 0;
                        while(pos < SIZE && !this->empty_space(i, pos)){++pos;}
                        if(pos >= j) continue;
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
            for(int i = SIZE - 1; i >= 0; --i)
            {
                for(int j = SIZE - 1; j >= 0; --j)
                {
                    if(!this->empty_space(i, j))
                    {
                        int pos = SIZE - 1;
                        while(pos >= 0 && !this->empty_space(i, pos)){--pos;}
                        if(pos <= j) continue;
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

void MainWindow::closeEvent(QCloseEvent *)
{
    this->write_record();
}

void MainWindow::create()
{
    int x, y;
    do
    {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while(!this->empty_space(x, y));

    if(rand() % 100 >= 10)
    {
       this->get_curr_item(x,y)->setData(Qt::UserRole, 2);
    }
    else
    {
       this->get_curr_item(x,y)->setData(Qt::UserRole, 4);
    }
    this->get_curr_item(x, y)->setText(ui->tableWidget->item(x,y)->data(Qt::UserRole).toString());
    this->check_color(this->get_curr_item(x, y));
}

void MainWindow::on_actionNew_Game_triggered()
{
    this->write_record();
    ui->tableWidget->clear();
    this->score = 0;
    this->update_status_bar();
    this->finish = false;
    this->fill();
    // create 2 blocks
    this->create();
    this->create();
}

void MainWindow::fill()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
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
    ui->tableWidget->item(row, column)->setFont(item->font());
}

void MainWindow::check_color(QTableWidgetItem * item)
{
    static const QString FONT_NAME = "Clear Sans";
    static const int MAX_FONT_SIZE = 28;
    static const QColor BACKGROUND_COLORS[] = {
        {204, 192, 179},
        {238, 226, 214},
        {239, 222, 194},
        {248, 175, 106},
        {253, 145, 81},
        {254, 123, 77},
        {205, 65, 5},
        {242, 204, 102},
        {240, 195, 78},
        {242, 192, 61},
        {242, 189, 51},
        {242, 182, 49},
        {41, 39, 27}
    };
    static const QColor TEXT_COLORS[] = {
        {50, 50, 50},
        {230, 230, 230}
    };

    auto data_temp = item->data(Qt::UserRole).toInt();

    item->setFont({FONT_NAME, MAX_FONT_SIZE - (data_temp > 10000 ? 15 : data_temp > 1000 ? 7 : 0)});
    item->setTextColor(TEXT_COLORS[data_temp > 4]);
    item->setBackgroundColor(BACKGROUND_COLORS[data_temp <= 2048 ? static_cast<int>(log10(data_temp)/log10(2))
                                                                 : _countof(BACKGROUND_COLORS) - 1]);

    if(data_temp == 2048 && !finish)
    {
        auto write = QtConcurrent::run([this]
        {
            this->write_record();
        });
        finish = true;
        Finish window(score);
        window.setModal(true);
        connect(&window, &Finish::new_game, this, &MainWindow::on_actionNew_Game_triggered);
        window.exec();
        write.waitForFinished();
    }
}

void MainWindow::merge_items(QTableWidgetItem * res)
{
    res->setData(Qt::UserRole, res->data(Qt::UserRole).toInt() << 1);
    res->setText(res->data(Qt::UserRole).toString());
    score += res->data(Qt::UserRole).toInt();
    this->update_status_bar();
    this->check_color(res);
}

void MainWindow::check_over() const
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            if(this->empty_space(i, j))
            {
                return;
            }
            auto temp_data = this->get_data_item(i, j);
            if(i < SIZE - 2 && temp_data == this->get_data_item(i + 1, j))
            {
                return;
            }
            else if(i > 0 && temp_data == this->get_data_item(i - 1, j))
            {
                return;
            }
            else if(j < SIZE - 2 && temp_data == this->get_data_item(i, j + 1))
            {
                return;
            }
            else if(j > 0 && temp_data == this->get_data_item(i, j - 1))
            {
                return;
            }
        }
    }
    auto write = QtConcurrent::run([this]
    {
        this->write_record();
    });
    ui->tableWidget->setDisabled(true);
    Over window(score);
    window.setModal(true);
    connect(&window, &Over::new_game, this, &MainWindow::on_actionNew_Game_triggered);
    window.exec();
    write.waitForFinished();
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

void MainWindow::read_record() const
{
    QFile file(RECORD_FILE_NAME);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream data(&file);
        data >> record;
        file.close();
    } else 
    {
        record = 0UL;
    }
}

void MainWindow::write_record() const
{
    if(score < record)
    {
        return;
    }
    record = score;
    QFile file(RECORD_FILE_NAME);
    file.open(QIODevice::WriteOnly);
    file.flush();
    QDataStream output(&file);
    output << record;
    file.close();
}

void MainWindow::update_status_bar() const
{
    this->statusBar()->showMessage("Record: " + QString::number(record > score ? record : score) + "    "
                                   "Score: "  + QString::number(score));
}