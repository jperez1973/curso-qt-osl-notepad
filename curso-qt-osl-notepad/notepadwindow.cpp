#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

    mnuArchivo_->addSeparator();

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon(":/imagen/recursos/libreoffice-oasis-drawing-template.png"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarUndo_ = new QAction(tr("&Deshacer"), this);
    actEditarUndo_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarUndo_);

    actEditarRedo_ = new QAction(tr("&Rehacer"), this);
    actEditarRedo_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRedo_);

    mnuEditar_->addSeparator();

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(tr("&Acerca de..."), this);
    mnuAyuda_->addAction(actAyudaAcerca_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    mainToolbar = new QToolBar(this);
    this->addToolBar(mainToolbar);
    mainToolbar->addAction(actEditarCortar_);
    mainToolbar->addAction(actEditarCopiar_);
    mainToolbar->addAction(actEditarPegar_);
    mainToolbar->addSeparator();
    mainToolbar->addAction(actArchivoSalir_);
    mainToolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);
    txtEditor_->setAcceptRichText(true);
    txtEditor_->setDocument(new QTextDocument(txtEditor_));

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actArchivoSalir_,   SIGNAL(triggered()), this,          SLOT(alSalir()));
    connect(actEditarUndo_,     SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(actEditarRedo_,     SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,    SLOT(cut()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(actAyudaAcerca_,    SIGNAL(triggered()), this,          SLOT(alAcerca()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    mnuArchivo_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    actArchivoSalir_->deleteLater();
    mnuEditar_->deleteLater();
    actEditarCortar_->deleteLater();
    actEditarUndo_->deleteLater();
    actEditarRedo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuFormato_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuAyuda_->deleteLater();
    actAyudaAcerca_->deleteLater();
    txtEditor_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "/home/temporal",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        if (! nombreArchivo.endsWith(".txt")) {
            nombreArchivo += ".txt";
        }
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}

void NotepadWindow::alSalir() {
    QMessageBox msgbox;
    msgbox.setText("¿Está ud. Seguro?");
    msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int val = msgbox.exec();
    if (val == QMessageBox::Yes) {
        close();
    }
}

void NotepadWindow::alAcerca() {
    QMessageBox msgbox;
    msgbox.setText("<b>Hola</b> mundo");
    msgbox.exec();
}
