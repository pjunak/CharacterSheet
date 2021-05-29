#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <toml++/toml.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    void SetupDesign();
    void updateChar();
    void setupChar();
    toml::table openTOML(toml::table tbl);
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
