#include "mainwindow.h"
#include "ui_mainwindow.h"

//Include for testing
#include <iostream>

//Include for TOML
#include <toml++/toml.h>
#include <fstream>

//Including for unsaved prograss notification on close
#include <QCloseEvent>
#include <QMessageBox>

//Including global variables
#include "globals.h"


/**
 * @brief MainWindow::MainWindow MainWindow class constructor
 * @details After constructing MainWindow calls functions for setting up chracter from user files
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->SetupDesign();

    this->setupChar(); //Sets up character info from data stored in config.toml
}

/**
 * @brief MainWindow::~MainWindow MainWindow class destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupDesign()
{
    // sets background
    this->setStyleSheet("MainWindow {background-image:url(:/resources/img/background.jpg);}"); //Sets background for MainWindow
    // Sets design frames for portrait, stats, proficiencies, abilities
    // Portrait
    QPixmap overlay(":/resources/img/portrait_frame.png");
    ui->Portrait_overlay->setPixmap(overlay);
    // Stats
    ui->Strength->setObjectName("named"); // Needs to be named to prevent style inheriting
    ui->Dexterity->setObjectName("named");
    ui->Constitution->setObjectName("named");
    ui->Inteligence->setObjectName("named");
    ui->Wisdom->setObjectName("named");
    ui->Charisma->setObjectName("named");
    ui->Strength->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");
    ui->Dexterity->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");
    ui->Constitution->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");
    ui->Inteligence->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");
    ui->Wisdom->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");
    ui->Charisma->setStyleSheet("QFrame#named{border-image: url(:/resources/img/stat_frame.png) 0 0 0 0 stretch stretch;}");

    //obsolete
    ui->Proficiencies_3->setObjectName("named");
    ui->Proficiencies_3->setStyleSheet("QFrame#named{border-image: url(:/resources/img/proficiency_frame.png) 0 0 0 0 stretch stretch;}");

    // Profciencies
    ui->Proficiencies->setObjectName("named");
    ui->Proficiencies->setStyleSheet("QTabWidget#named{ background-color: transparent;}");
    // Proficiency tabs
    ui->Armor_tab->setObjectName("named");
    ui->Weapons_tab->setObjectName("named");
    ui->Tools_tab->setObjectName("named");
    ui->Languages_tab->setObjectName("named");
    ui->Armor_tab->setStyleSheet("QWidget#named{ background-color: transparent;}");
    ui->Weapons_tab->setStyleSheet("QWidget#named{ background-color: transparent;}");
    ui->Tools_tab->setStyleSheet("QWidget#named{ background-color: transparent;}");
    ui->Languages_tab->setStyleSheet("QWidget#named{ background-color: transparent;}");
    // Proficiency frames
    ui->Armor_Frame->setObjectName("named");
    ui->Weapons_frame->setObjectName("named");
    ui->Tools_frame->setObjectName("named");
    ui->Languages_frame->setObjectName("named");
    ui->Armor_Frame->setStyleSheet("QFrame#named{border-image: url(:/resources/img/frame_pointy_wide.png) 0 0 0 0 stretch stretch;}");
    ui->Weapons_frame->setStyleSheet("QFrame#named{border-image: url(:/resources/img/frame_pointy_wide.png) 0 0 0 0 stretch stretch;}");
    ui->Tools_frame->setStyleSheet("QFrame#named{border-image: url(:/resources/img/frame_pointy_wide.png) 0 0 0 0 stretch stretch;}");
    ui->Languages_frame->setStyleSheet("QFrame#named{border-image: url(:/resources/img/frame_pointy_wide.png) 0 0 0 0 stretch stretch;}");

}




/**
 * @brief getQStrVal Returns value from TOML node converted to QString
 * @param node TOML file node
 * @return Returns either succesfully loaded QString or empty QString if node contains no value
 */
QString getQStrVal(toml::v2::node_view<toml::v2::node> node)
{
    return QString::fromStdString(node.value<std::string>().value_or(""));
}

/**
 * @brief getIntVal Returns value from TOML node converted to int
 * @param node TOML file node
 * @return Returns either succesfully loaded int or 0 if node contains no value
 */
int getIntVal(toml::v2::node_view<toml::v2::node> node)
{
    return node.value<int>().value_or(0);
}

std::vector<QString> getVectorVal(toml::v2::node_view<toml::v2::node> node)
{
    std::vector<QString> vector;
    if ( toml::array* item = node.as_array())
    {
        for (toml::node& item : *item)
        {
            vector.push_back(QString::fromStdString(item.value_or("")));
        }
    }
    else{
        vector.push_back(QString::fromStdString("Error loading from file"));
    }
    return vector;
}

toml::table MainWindow::openTOML(toml::table tbl)
{
    try
    {
        tbl = toml::parse_file("../CharacterSheet/character/character.toml");
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

/**
 * @brief MainWindow::updateChar Updates displayed character info from data in character_data
 * @details Is called every time any change to character_data is made
 */
void MainWindow::updateChar()
{
    // Concatenates full name from its parts and displays it
    QString fullName;
    fullName += Ch.Name.title_before;
    if (fullName.length() > 0 && Ch.Name.first.length() > 0)
    {
            fullName += " ";
    }
    fullName += Ch.Name.first;
    if (fullName.length() > 0 && Ch.Name.middle.length() > 0)
    {
            fullName += " ";
    }
    fullName += Ch.Name.middle;
    if (fullName.length() > 0 && Ch.Name.last.length() > 0)
    {
            fullName += " ";
    }
    fullName += Ch.Name.last;
    if (fullName.length() > 0 && Ch.Name.title_after.length() > 0)
    {
            fullName += " ";
    }
    fullName += Ch.Name.title_after;
    ui->Name->setText(fullName);

    // Sets all attributes and modifiers
    // Strength
    ui->STR_val->setNum(Ch.Att.STR);
    ui->STR_mod->setNum((Ch.Att.STR - 10)/2);
    if (ui->STR_mod->text().QString::toInt() > 0)
    {
        ui->STR_mod->setStyleSheet("color:green");
    }else if (ui->STR_mod->text().QString::toInt() < 0)
    {
        ui->STR_mod->setStyleSheet("color:red");
    }else
    {
        ui->STR_mod->setStyleSheet("color:black");
    }
    // Dexterity
    ui->DEX_val->setNum(Ch.Att.DEX);
    ui->DEX_mod->setNum((Ch.Att.DEX - 10)/2);
    if (ui->DEX_mod->text().QString::toInt() > 0)
    {
        ui->DEX_mod->setStyleSheet("color:green");
    }else if (ui->DEX_mod->text().QString::toInt() < 0)
    {
        ui->DEX_mod->setStyleSheet("color:red");
    }else
    {
        ui->DEX_mod->setStyleSheet("color:black");
    }
    // Constitution
    ui->CON_val->setNum(Ch.Att.CON);
    ui->CON_mod->setNum((Ch.Att.CON - 10)/2);
    if (ui->CON_mod->text().QString::toInt() > 0)
    {
        ui->CON_mod->setStyleSheet("color:green");
    }else if (ui->CON_mod->text().QString::toInt() < 0)
    {
        ui->CON_mod->setStyleSheet("color:red");
    }else
    {
        ui->CON_mod->setStyleSheet("color:black");
    }
    // Inteligence
    ui->INT_val->setNum(Ch.Att.INT);
    ui->INT_mod->setNum((Ch.Att.INT - 10)/2);
    if (ui->INT_mod->text().QString::toInt() > 0)
    {
        ui->INT_mod->setStyleSheet("color:green");
    }else if (ui->INT_mod->text().QString::toInt() < 0)
    {
        ui->INT_mod->setStyleSheet("color:red");
    }else
    {
        ui->INT_mod->setStyleSheet("color:black");
    }
    // Wisdom
    ui->WIS_val->setNum(Ch.Att.WIS);
    ui->WIS_mod->setNum((Ch.Att.WIS - 10)/2);
    if (ui->WIS_mod->text().QString::toInt() > 0)
    {
        ui->WIS_mod->setStyleSheet("color:green");
    }else if (ui->WIS_mod->text().QString::toInt() < 0)
    {
        ui->WIS_mod->setStyleSheet("color:red");
    }else
    {
        ui->WIS_mod->setStyleSheet("color:black");
    }
    // Charisma
    ui->CHA_val->setNum(Ch.Att.CHA);
    ui->CHA_mod->setNum((Ch.Att.CHA - 10)/2);
    if (ui->CHA_mod->text().QString::toInt() > 0)
    {
        ui->CHA_mod->setStyleSheet("color:green");
    }else if (ui->CHA_mod->text().QString::toInt() < 0)
    {
        ui->CHA_mod->setStyleSheet("color:red");
    }else
    {
        ui->CHA_mod->setStyleSheet("color:black");
    }

    // Sets all proficiencies
    ui->Armor_prof->setText("");
    ui->Armor_prof->setWordWrap(true);
    ui->Weapons_prof->setText("");
    ui->Weapons_prof->setWordWrap(true);
    ui->Tools_prof->setText("");
    ui->Tools_prof->setWordWrap(true);
    ui->Languages_prof->setText("");
    ui->Languages_prof->setWordWrap(true);
    for (auto &&item : Ch.Prof.armor)
    {
        ui->Armor_prof->setText(ui->Armor_prof->text() + item);
        if (item != Ch.Prof.armor.back())
        {
            ui->Armor_prof->setText(ui->Armor_prof->text() + ", ");
        }
    }
    for (auto &&item : Ch.Prof.weapons)
    {
        ui->Weapons_prof->setText(ui->Weapons_prof->text() + item);
        if (item != Ch.Prof.weapons.back())
        {
            ui->Weapons_prof->setText(ui->Weapons_prof->text() + ", ");
        }
    }
    for (auto &&item : Ch.Prof.tools)
    {
        ui->Tools_prof->setText(ui->Tools_prof->text() + item);
        if (item != Ch.Prof.tools.back())
        {
            ui->Tools_prof->setText(ui->Tools_prof->text() + ", ");
        }
    }
    for (auto &&item : Ch.Prof.languages)
    {
        ui->Languages_prof->setText(ui->Languages_prof->text() + item);
        if (item != Ch.Prof.languages.back())
        {
            ui->Languages_prof->setText(ui->Languages_prof->text() + ", ");
        }
    }

}

/**
 * @brief MainWindow::setupChar Loads data from save file
 * @details Loads data from character.toml file into character_data Ch struct
 */
void MainWindow::setupChar()
{
    // Loads and displays portrait
    QPixmap portrait("../CharacterSheet/character/portrait.jpg");
    ui->Portrait->setPixmap(portrait);


    // Opens character save file
    toml::table character;
    character = openTOML(character);

    Ch.Name.title_before = getQStrVal(character["name"]["title_before"]);
    Ch.Name.first = getQStrVal(character["name"]["first"]);
    Ch.Name.middle = getQStrVal(character["name"]["middle"]);
    Ch.Name.last = getQStrVal(character["name"]["last"]);
    Ch.Name.title_after = getQStrVal(character["name"]["title_after"]);

    Ch.Att.STR = getIntVal(character["attribute"]["STR"]);
    Ch.Att.DEX = getIntVal(character["attribute"]["DEX"]);
    Ch.Att.CON = getIntVal(character["attribute"]["CON"]);
    Ch.Att.INT = getIntVal(character["attribute"]["INT"]);
    Ch.Att.WIS = getIntVal(character["attribute"]["WIS"]);
    Ch.Att.CHA = getIntVal(character["attribute"]["CHA"]);

    Ch.Prof.armor = getVectorVal(character["proficiency"]["armor"]);
    Ch.Prof.weapons = getVectorVal(character["proficiency"]["weapons"]);
    Ch.Prof.tools = getVectorVal(character["proficiency"]["tools"]);
    Ch.Prof.languages = getVectorVal(character["proficiency"]["languages"]);

    updateChar();
}

/**
 * @brief MainWindow::closeEvent Shows prompt for user when program is closed
 * @param event Catches program closing event
 */
void MainWindow::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }

}
