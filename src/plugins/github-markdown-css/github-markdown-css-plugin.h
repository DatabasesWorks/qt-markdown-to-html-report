#ifndef CGITHUBMARKCSS_PLUGIN_H
#define CGITHUBMARKCSS_PLUGIN_H

#include <QtPlugin>
#include "markdown-qt.h"

class CGithubMarkdownCssPlugin : public PluginBaseMdQt
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginBaseMdQt_iid)
    Q_INTERFACES(PluginBaseMdQt)

public:
    CGithubMarkdownCssPlugin();
    ~CGithubMarkdownCssPlugin() override;
    virtual QList<ConvertType> availableConversions() override;
    virtual QString displayName() override;
    virtual bool convert(ConvertType convertType, const QByteArray dataIn, QByteArray& dataOut) override;
    virtual bool addFraming(CMarkDownQt::DataFormat dataFormat, const QByteArray dataIn, QByteArray& dataOut) override;
private:
    QByteArray cssHtml(QByteArray strHtmlIn);
};

#endif // CGITHUBMARKCSS_PLUGIN_H
