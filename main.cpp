#include <iostream>
#include <QApplication>

#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <QMediaPlayer>


class ImageButton : public QPushButton {
Q_OBJECT
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);//конструктор встраивает наш виджет в родительский(parent)
    void paintEvent(QPaintEvent *e) override;//переопределяем эти методы
    QSize sizeHint() const override;//дальше они будут расписаны
    QSize minimumSizeHint() const override;//
    void keyPressEvent(QKeyEvent *e) override;//
public slots:
    void setUp();
    void setDown();

private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("Stop");//подсказка при наведении на кнопку
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);//размеры виджета(фикс.)
    mButtonUpPixmap = QPixmap("D:\\c++\\Home Task 38\\Sound_Button\\button.png");
    mButtonDownPixmap = QPixmap("D:\\c++\\Home Task 38\\Sound_Button\\pushed_button.png");
    mCurrentButtonPixmap = mButtonUpPixmap;//задание ненажатой кнопки
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);//this - тк речь об этой кнопке, connect - тк работаем в наследственном классе QPushButton
}

void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}
QSize ImageButton::sizeHint() const {
    return QSize(100, 100);
}
QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}
void ImageButton::setDown() {
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();//для перерисовки виджета, иначе Qt не будет знать что что-то изменилось
    QTimer::singleShot(400, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(100, 100);
    redButton.move(1000, 400);

    auto *button = new QMediaPlayer(&redButton);

    QObject::connect(&redButton, &QPushButton::clicked, [button](){
        button->setMedia(QUrl::fromLocalFile("D:\\c++\\Home Task 38\\Sound_Button\\pushSound.mp3"));

        button->setVolume(100);
        button->play();
    });
    redButton.show();

    return QApplication::exec();
}
#include "main.moc"
