#include "mainwindow.h"
#include "ui_mainwindow.h"

//Include for testing
#include <QMessageBox>

//Include for TOML
#include <toml++/toml.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include <QFrame>


//Including global variables
#include "globals.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("MainWindow {background-image:url(:/resources/resources/img/background.jpg);}"); //Sets background for MainWindow
    this->setupCharacter(); //Sets up character info from data stored in config.toml

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString getQStrVal(toml::v2::node_view<toml::v2::node> node)
{
    return QString::fromStdString(node.value<std::string>().value_or(""));
}

toml::table MainWindow::openTOML(toml::table tbl)
{
    try
    {
        tbl = toml::parse_file("../CharacterSheet/character/config.toml");
    }
    catch (const toml::parse_error& err)
    {
        QMessageBox msgBox;
        msgBox.setText("Error parsing the TOML file");
        msgBox.exec();

        std::cerr << "Parsing failed:\n" << err << "\n";
        errorCode = 1;
    }
    return tbl;
}

void MainWindow::setupCharacter()
{
    toml::table character;
    character = openTOML(character);

    QString fullName;
    if (getQStrVal(character["char_name"]["title_before"]).length() > 0)
    {
            fullName += getQStrVal(character["char_name"]["first"]);
    }
    if (getQStrVal(character["char_name"]["first"]).length() > 0)
    {
            fullName += " " + getQStrVal(character["char_name"]["first"]);
    }
    if (getQStrVal(character["char_name"]["middle"]).length() > 0)
    {
            fullName += " " + getQStrVal(character["char_name"]["middle"]);
    }
    if (getQStrVal(character["char_name"]["last"]).length() > 0)
    {
            fullName += " " + getQStrVal(character["char_name"]["last"]);
    }
    if (getQStrVal(character["char_name"]["title_after"]).length() > 0)
    {
            fullName += " " + getQStrVal(character["char_name"]["title_after"]);
    }
    ui->Name->setText(fullName);

    ui->STR_val->setText(getQStrVal(character["attributes"]["STR"]));
    ui->DEX_val->setText(getQStrVal(character["attributes"]["DEX"]));
    ui->CON_val->setText(getQStrVal(character["attributes"]["CON"]));
    ui->INT_val->setText(getQStrVal(character["attributes"]["INT"]));
    ui->WIS_val->setText(getQStrVal(character["attributes"]["WIS"]));
    ui->CHA_val->setText(getQStrVal(character["attributes"]["CHA"]));




    ui->Portrait->setStyleSheet("border: 2px solid black;");


}


