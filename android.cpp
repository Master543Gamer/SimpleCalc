#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QJSEngine>
#include <QJSValue>
#include <QString>
#include <QDebug>
#include <QKeyEvent>

class SimplCalcQt : public QMainWindow {
    Q_OBJECT

public:
    SimplCalcQt(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        QWidget *central = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(central);
        mainLayout->setContentsMargins(8, 8, 8, 8);
        mainLayout->setSpacing(8);

        // Display
        display = new QPlainTextEdit();
        display->setPlaceholderText("Type here");

        QFont font;
        // On Android pixel sizes behave more predictably:
        font.setPixelSize(48);
        display->setFont(font);

        // Let the display take only a bit of vertical space (not huge)
        display->setFixedHeight(120); // modest height for mobile, tweak if needed
        mainLayout->addWidget(display);

        // Install event filter for Enter key
        display->installEventFilter(this);

        // Button grid
        QGridLayout *buttonLayout = new QGridLayout();
        buttonLayout->setSpacing(6);

        QString buttons[5][3] = {
            {"1", "2", "3"},
            {"4", "5", "6"},
            {"7", "8", "9"},
            {"-", "0", "+"},
            {"*", "/", "="}
        };

        QFont fontBtn;
        fontBtn.setPixelSize(64); // bigger on mobile

        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 3; ++col) {
                QString text = buttons[row][col];
                QPushButton *btn = new QPushButton(text);
                btn->setFont(fontBtn);

                // Make buttons expand to fill available space — good for touch
                btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                // Prefer not to set fixed sizes on mobile
                buttonLayout->addWidget(btn, row, col);

                connect(btn, &QPushButton::clicked, this, [=]() {
                    onButtonClick(text);
                });
            }
        }

        // Make the buttons area expand to fill remaining space
        QWidget *buttonsWidget = new QWidget();
        buttonsWidget->setLayout(buttonLayout);
        mainLayout->addWidget(buttonsWidget, /*stretch=*/1);

        // Footer simple label
        QLabel *label = new QLabel("SimplCalcQt v3.1");
        label->setAlignment(Qt::AlignLeft);
        mainLayout->addWidget(label);

        setCentralWidget(central);

        // NOTE: do not call setFixedSize() on Android — let system handle sizing
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == display && event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            // Enter / Return => evaluate
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                onButtonClick("=");
                return true; // handled
            }
            // Shift+Enter: insert newline (if you want multiline)
            if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
                && (keyEvent->modifiers() & Qt::ShiftModifier)) {
                // Let QPlainTextEdit handle newline — do nothing special
                return false;
            }
        }
        return QMainWindow::eventFilter(obj, event);
    }

private slots:
    void onButtonClick(const QString &text) {
        if (text == "=") {
            QString expr = display->toPlainText();
            QJSEngine engine;
            // optional: sanitize expression here if needed
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
    // Enable high DPI scaling on mobile
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    SimplCalcQt window;
    window.showMaximized(); // on mobile show full screen
    return app.exec();
}

#include "main.moc"
