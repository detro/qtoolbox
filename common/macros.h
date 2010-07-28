/** Namespace Macro: begin. */
#define QTB_BEGIN_NAMESPACE namespace QTB {
/** Namespace Macro: end. */
#define QTB_END_NAMESPACE }

// TODO: This is temporary, while the proper debug macros part of this project gets submitted
#include <QDebug>
#define DEBUG(x) qDebug() << x;
#define DEBUG_TAG(tag, x) qDebug() << "[" << tag << "]" << x;
#define WARNING(x) qDebug() << x;
#define WARNING_TAG(tag, x) qDebug() << "[" << tag << "]" << x;
#define VERBOSE(x) qDebug() << x;
#define VERBOSE_TAG(tag, x) qDebug() << "[" << tag << "]" << "(verbose)" x;
