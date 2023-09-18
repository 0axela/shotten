#ifndef VUEPIOCHE_H
#define VUEPIOCHE_H

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

class VuePioche : public QPushButton {
    Q_OBJECT
public:
    explicit VuePioche(QWidget *parent = nullptr) : QPushButton(parent) {}
    virtual ~VuePioche() = default;
};

#endif // VUEPIOCHE_H
