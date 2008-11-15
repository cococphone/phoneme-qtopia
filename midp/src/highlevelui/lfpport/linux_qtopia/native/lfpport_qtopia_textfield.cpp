#include "lfpport_qtopia_textfield.h"
#include <lfpport_textfield.h>

//!TODO input constraints, size constraints

extern "C"
{
  MidpError lfpport_textfield_create(MidpItem *itemPtr, MidpDisplayable *ownerPtr, const pcsl_string *label,
                                     int layout, const pcsl_string *text, int maxSize, int constraints,
                                     const pcsl_string *initialInputMode)
  {
    JTextField *tf = new JTextField(item, ownerPtr->widgetPtr,
                                    pcls_string2QString(*label), layout, pcls_string2QString(*text),
                                        maxSize, constraints, pcls_string2QString(*initialInputMode));
    if (!tf)
      return KNI_ENOMEM;
    return KNI_OK;
  }

  MidpError lfpport_textfield_set_string(MidpItem *itemPtr, const pcsl_string *text)
  {
    JTextField *tf = (JTextField *)itemPtr->widgetPtr;
    return tf->setString(pcsl_string2QString(*text));
  }

  MidpError lfpport_textfield_get_string(pcsl_string *text, jboolean *newChange, MidpItem *itemPtr)
  {
    JTextField *tf = (JTextField *)itemPtr->widgetPtr;
    return QString2pcsl_string(tf->getString(newChange), *text);
  }

  MidpError lfpport_textfield_set_max_size(MidpItem *itemPtr, int maxSize)
  {
    JTextField *tf = (JTextField *)itemPtr->widgetPtr;
    return tf->setMaxSize(maxSize);
  }

  MidpError lfpport_textfield_get_caret_position(int *position, MidpItem *itemPtr)
  {
    JTextField *tf = (JTextField *)itemPtr->widgetPtr;
    *position = tf->getCaretPosition();
    return KNI_OK;
  }

  MidpError lfpport_textfield_set_constraints(MidpItem *itemPtr, int constraints)
  {
    JTextField *tf = (JTextField *)itemPtr->widgetPtr;
    return tf->setConstraints(constraints);
  }
}

JTextField::JTextField(MidpItem *item, JForm *form,
                       QString labelText, int layout, QString text,
                       int maxSize, int constraints, QString initialInputMode)
  : JItem(item, form)
{
  (void) layout;
  (void) maxSize;
  (void) constraints;
  (void) initialInputMode;

  QFormLayout *layout = new QFormLayout(this);
  layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
  tf_label = new QLabel(labelText, this);
  tf_body = new ExpandableTextEdit(text, this);
  tf_label->setBuddy(tf_body);
  tf_label->setTextFormat(Qt::PlainText);
  layout->addRow(tf_label, tf_body);

  cont_changed = false;
  connect(tf_body, SIGNAL(textChanged()), SLOT(contentsModified()));
}

JTextField::~JTextField()
{
}

void JTextField::j_setLabel(const QString &text)
{
  tf_label->setText(text);
}

MidpError JTextField::setString(const QString &text)
{
  tf_body->setText(text);
}

QString JTextField::getString(jboolean *changed)
{
  *changed = cont_changed;
  cont_changed = false;
  return tf_body->text();
}

MidpError JTextField::setMaxSize(int size)
{
}

int JTextField::getCaretPosition()
{
  return tf_body->textCursor().position();
}

MidpError JTextField::setConstraints(int constr)
{
}

void contentsModified()
{
  cont_changed = true;
}



