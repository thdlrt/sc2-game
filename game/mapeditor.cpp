#include "mapeditor.h"
#include "ui_mapeditor.h"

mapEditor::mapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapEditor)
{
    ui->setupUi(this);
}

mapEditor::~mapEditor()
{
    delete ui;
}
