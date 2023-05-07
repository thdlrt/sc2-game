#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QDialog>
#include"gamedata.h"
namespace Ui {
class mapEditor;
}

class mapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit mapEditor(QWidget *parent = nullptr);
    ~mapEditor();

private:
    Ui::mapEditor *ui;
};

#endif // MAPEDITOR_H
