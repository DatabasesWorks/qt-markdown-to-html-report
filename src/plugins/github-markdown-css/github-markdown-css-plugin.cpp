#include "github-markdown-css-plugin.h"
#include <QFile>

CGithubMarkdownCssPlugin::CGithubMarkdownCssPlugin()
{
    Q_INIT_RESOURCE(github_markdown_css);
}

CGithubMarkdownCssPlugin::~CGithubMarkdownCssPlugin()
{
}

QList<PluginInterfaceMdQt::ConvertType> CGithubMarkdownCssPlugin::availableConversions()
{
    QList<PluginInterfaceMdQt::ConvertType> supported;
    supported.append({CMarkDownQt::FormatHtmlUtf8, CMarkDownQt::FormatHtmlUtf8});
    return supported;
}

QString CGithubMarkdownCssPlugin::displayName()
{
    return QStringLiteral("github-markdown-css");
}

bool CGithubMarkdownCssPlugin::convert(ConvertType convertType, const QByteArray dataIn, QByteArray& dataOut)
{
    bool bSupported = false;
    if(convertType.inFormat==CMarkDownQt::FormatHtmlUtf8 &&
            convertType.inFormat==CMarkDownQt::FormatHtmlUtf8) {
        dataOut = cssHtml(dataIn);
    }
    return bSupported;
}

bool CGithubMarkdownCssPlugin::addFraming(CMarkDownQt::DataFormat dataFormat, const QByteArray dataIn, QByteArray& dataOut)
{
    bool bConverted = false;
    if(dataFormat == CMarkDownQt::FormatHtmlUtf8) {
        QByteArray strHeader;
        QFile fileHeader(QStringLiteral(":/github-styles/header"));
        if(fileHeader.exists() && fileHeader.open(QFile::ReadOnly | QFile::Unbuffered)) {
            strHeader = fileHeader.readAll();
            fileHeader.close();
        }
        QByteArray strFooter;
        QFile fileFooter(QStringLiteral(":/common-styles/footer"));
        if(fileFooter.exists() && fileFooter.open(QFile::ReadOnly | QFile::Unbuffered)) {
            strFooter = fileFooter.readAll();
            fileFooter.close();
        }
        dataOut = strHeader + dataIn + strFooter;
        bConverted = true;
    }
    return bConverted;
}


QByteArray CGithubMarkdownCssPlugin::cssHtml(QByteArray strHtmlIn)
{
    QByteArray strHtmlOut;
    QString strStyleName = QStringLiteral(":/github-markdown-css-source/github-markdown.css");
    QString strStyleFooterName = QStringLiteral(":/github-styles/footer");
    QByteArray strStyle;
    QFile fileStyle(strStyleName);
    if(fileStyle.exists() && fileStyle.open(QFile::ReadOnly | QFile::Unbuffered)) {
        strStyle = fileStyle.readAll();
        fileStyle.close();
    }
    QByteArray strStyleFooter;
    QFile fileStyleFooter(strStyleFooterName);
    if(fileStyleFooter.exists() && fileStyleFooter.open(QFile::ReadOnly | QFile::Unbuffered)) {
        strStyleFooter = fileStyleFooter.readAll();
        fileStyleFooter.close();
    }
    strHtmlOut =
            strStyle +
            strStyleFooter +
            strHtmlIn;
    return strHtmlOut;
}
