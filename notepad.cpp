#include "notepad.h"
#include "ui_notepad.h"

bool isFontChanged = false;

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    // Setting the default font of Text Edit widget
    if (!isFontChanged)
        ui->textEdit->setFont(QFont("Consolas", 14));
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    currentFilename.clear();
    ui->textEdit->setText(QString());
}


void Notepad::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    currentFilename = filename;
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Notepad::on_actionSave_triggered()
{
    QString filename;
    if (currentFilename.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "Save");
        if (filename.isEmpty())
            return;
        currentFilename = filename;
    }
    else
        filename = currentFilename;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save As");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFilename = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionExit_triggered()
{
    QCoreApplication::exit();
}


void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Notepad::on_actionFont_Options_triggered()
{
    bool fontSelected;
    QFont currentFont = ui->textEdit->currentFont();
    QFont font = QFontDialog::getFont(&fontSelected, QFont(currentFont), this, "Select a Font");
    if (fontSelected) {
        ui->textEdit->setFont(font);
        isFontChanged = true;
    }
}


void Notepad::on_actionBold_triggered()
{
    if (ui->textEdit->textCursor().hasSelection()) {
        QTextCharFormat format;
        if (!ui->textEdit->textCursor().charFormat().font().bold())
            format.setFontWeight(QFont::Bold);
        else
            format.setFontWeight(1);
        mergeFormatOnSelection(format);
    }
}


void Notepad::on_actionSuperscript_triggered()
{
    if (ui->textEdit->textCursor().hasSelection()) {
        QTextCharFormat format;
        if (!ui->textEdit->textCursor().charFormat().font().bold())
            format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
        else
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
        mergeFormatOnSelection(format);
    }
}


void Notepad::on_actionSubscript_triggered()
{
    if (ui->textEdit->textCursor().hasSelection()) {
        QTextCharFormat format;
        if (!ui->textEdit->textCursor().charFormat().font().bold())
            format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
        else
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
        mergeFormatOnSelection(format);
    }
}


void Notepad::on_actionZoom_In_triggered()
{
    QFont font = ui->textEdit->currentFont();
    if (font.pointSize() > 72)
        return;
    font.setPointSize(font.pointSize() + 2);
    ui->textEdit->setFont(font);
}


void Notepad::on_actionZoom_Out_triggered()
{
    QFont font = ui->textEdit->currentFont();
    if (font.pointSize() < 8)
        return;
    font.setPointSize(font.pointSize() - 2);
    ui->textEdit->setFont(font);
}


void Notepad::mergeFormatOnSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        return;
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void Notepad::on_actionAbout_Me_triggered()
{
    AboutMe aboutMe;
    aboutMe.setWindowTitle("Resume");
    aboutMe.setWindowIcon(QIcon(":/images/resources/info-32.png"));
    aboutMe.setModal(true);
    aboutMe.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    aboutMe.exec();
}

