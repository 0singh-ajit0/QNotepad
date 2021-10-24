#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QTextDocument>
#include <QTextCharFormat>
#include "aboutme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionFont_Options_triggered();

    void on_actionBold_triggered();

    void on_actionSuperscript_triggered();

    void on_actionSubscript_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionAbout_Me_triggered();

private:
    Ui::Notepad *ui;
    QString currentFilename;
    void mergeFormatOnSelection(const QTextCharFormat &format);
};
#endif // NOTEPAD_H
