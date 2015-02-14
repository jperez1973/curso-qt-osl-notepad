#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alSalir();
    void alAcerca();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarUndo_;
    QAction*        actEditarRedo_;
    QAction*        actEditarCortar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaAcerca_;
    QTextEdit*      txtEditor_;
    QToolBar*       mainToolbar;
};

#endif // NOTEPADWINDOW_H
