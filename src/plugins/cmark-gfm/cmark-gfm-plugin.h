#ifndef CMARKGFM_PLUGIN_H
#define CMARKGFM_PLUGIN_H

#include <QtPlugin>
#include "markdown-qt.h"

class CMarkGfmPlugin : public QObject, public MdQtPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MdQtPluginInterface_iid)
    Q_INTERFACES(MdQtPluginInterface)

public:
    ~CMarkGfmPlugin() override {}
    virtual QList<ConvertType> availableConversion() override;
    virtual QString displayName() override;
    virtual bool convert(ConvertType convertType, const QByteArray strIn, QByteArray& strOut) override;
private:
    QByteArray convertToHtml(QByteArray strMarkDownUtf8);
};

#endif // CMARKGFM_PLUGIN_H
