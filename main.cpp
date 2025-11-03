#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QMenuBar>
#include <QFont>
#include <QJSEngine>
#include <QJSValue>
#include <QString>
#include <QDebug>

class SimplCalcQt : public QMainWindow {
    Q_OBJECT

public:
        SimplCalcQt(QWidget *parent = nullptr)
: QMainWindow(parent)
{
    setWindowTitle("SimplCalcQt v3.0");
resize(310, 678);

QWidget *central = new QWidget(this);
QVBoxLayout *mainLayout = new QVBoxLayout(central);
mainLayout->setContentsMargins(10, 10, 10, 10);
mainLayout->setSpacing(10);

// Display
display = new QPlainTextEdit();
display->setPlaceholderText("Type here");
QFont font;
font.setPointSize(16);
display->setFont(font);
display->setFixedHeight(80);
mainLayout->addWidget(display);

// Button grid
QGridLayout *buttonLayout = new QGridLayout();
buttonLayout->setSpacing(10);

QString buttons[5][3] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"},
    {"-", "0", "+"},
    {"*", "/", "="}
};

QFont fontBtn;
fontBtn.setPointSize(36);

for (int row = 0; row < 5; ++row) {
for (int col = 0; col < 3; ++col) {
    QString text = buttons[row][col];
QPushButton *btn = new QPushButton(text);
                                   btn->setFont(fontBtn);
                                                btn->setFixedSize(88, 91);
                                                                  buttonLayout->addWidget(btn, row, col);

connect(btn, &QPushButton::clicked, this, [=]() {
    onButtonClick(text);
                                           });
                                           }
                                           }

                                           mainLayout->addLayout(buttonLayout);

                                           // Footer
                                           QLabel *label = new QLabel("SimplCalcQt v3.0");
                                           label->setAlignment(Qt::AlignLeft);
                                           mainLayout->addWidget(label);

                                           // Menubar & statusbar
                                           setMenuBar(new QMenuBar());
                                           setStatusBar(new QStatusBar());

                                           setCentralWidget(central);
                                           }

                                           private slots:
                                               void onButtonClick(const QString &text) {
                                               if (text == "=") {
                                               QString expr = display->toPlainText();
                                           QJSEngine engine;
                                           QJSValue result = engine.evaluate(expr);
                                           if (result.isError()) {
                                               display->setPlainText("Error");
                                           } else {
                                               display->setPlainText(result.toString());
                                           }
                                           } else {
                                               display->insertPlainText(text);
                                           }
                                           }

                                           private:
                                               QPlainTextEdit *display;
                                           };

                                           int main(int argc, char *argv[]) {
                                               QApplication app(argc, argv);
                                           SimplCalcQt window;
                                           window.show();
                                           return app.exec();
                                           }

                                           #include "main.moc"
                                           