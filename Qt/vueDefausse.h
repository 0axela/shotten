
#ifndef VUEDEFAUSSE_H
#define VUEDEFAUSSE_H

#include "st.h"
#include"vueSettings.h"
//#include "vuePartie.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <vector>

class VueDefausse : public QPushButton {
    Q_OBJECT
public:
    explicit VueDefausse(QWidget *parent = nullptr) : QPushButton(parent) {}
    virtual ~VueDefausse() = default;
};

#endif // VUEDEFAUSSE_H
