<?xml version="1.0" encoding="UTF-8"?> 
<!--
    Default stylesheet for Panda documentation, still pretty sparse.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" indent="yes"/>

    <xsl:template name="countSubstrings">
        <xsl:param name="haystack"/>
        <xsl:param name="needle"/>
        
        <xsl:choose>
            <xsl:when test="contains($haystack, $needle) and $haystack and $needle">
                <xsl:variable name="count">
                    <xsl:call-template name="countSubstrings">
                        <xsl:with-param name="haystack" select="substring-after($haystack, $needle)"/>
                        <xsl:with-param name="needle" select="$needle"/>
                    </xsl:call-template>
                </xsl:variable>
                <xsl:value-of select="$count + 1"/>
            </xsl:when>
            <xsl:otherwise>0</xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template name="repeatString">
        <xsl:param name="text"/>
        <xsl:param name="count"/>
        <xsl:if test="$count &gt; 0">
            <xsl:value-of select="$text"/>
            <xsl:call-template name="repeatString">
                <xsl:with-param name="text" select="$text"/>
                <xsl:with-param name="count" select="$count - 1"/>
            </xsl:call-template>
        </xsl:if>
    </xsl:template>

    <xsl:template name="replaceString">
        <xsl:param name="haystack"/>
        <xsl:param name="needle"/>
        <xsl:param name="replacement"/>
        <xsl:choose>
            <xsl:when test="contains($haystack, $needle)">
                <xsl:value-of select="substring-before($haystack, $needle)"/>
                <xsl:value-of select="$replacement"/>
                <xsl:call-template name="replaceString">
                    <xsl:with-param name="haystack"
                            select="substring-after($haystack, $needle)"/>
                    <xsl:with-param name="needle" select="$needle"/>
                    <xsl:with-param name="replacement" select="$replacement"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="$haystack"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template name="basePath">
        <xsl:param name="className"/>
        <xsl:variable name="count">
            <xsl:call-template name="countSubstrings">
                <xsl:with-param name="haystack" select="$className"/>
                <xsl:with-param name="needle" select="'.'"/>
            </xsl:call-template>
        </xsl:variable>
        <xsl:call-template name="repeatString">
            <xsl:with-param name="text" select="'../'"/>
            <xsl:with-param name="count" select="$count"/>
        </xsl:call-template>
    </xsl:template>

    <xsl:template name="packageName">
        <xsl:param name="name"/>
        <xsl:if test="contains($name, '.')">
            <xsl:value-of select="substring-before($name, '.')"/>
            <xsl:if test="contains(substring-after($name, '.'), '.')">
                <xsl:text>.</xsl:text>
                <xsl:call-template name="packageName">
                    <xsl:with-param name="name" 
                            select="substring-after($name, '.')"/>
                </xsl:call-template>
            </xsl:if>
        </xsl:if>
    </xsl:template>

    <xsl:template name="baseName">
        <xsl:param name="name"/>
        <xsl:choose>
            <xsl:when test="contains($name, '&lt;')">
                <xsl:value-of select="substring-before($name, '&lt;')"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="$name"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="/packages">
        <ul>
            <xsl:apply-templates/>
        </ul>
    </xsl:template>

    <xsl:template match="/packages/package">
        <li id="package{name}" class="collapse">
          <a href="{path}"><xsl:value-of select="name"/></a>
          <ul>
            <xsl:apply-templates select="classes"/>
          </ul>
        </li>
    </xsl:template>

    <xsl:template match="/packages/package/classes/class">
        <li><a href="api/{path}"><xsl:value-of select="name"/></a></li>
    </xsl:template>

    <xsl:template name="toc">
      @@@TOC@@@
    </xsl:template>

    <xsl:template match="/class">
        <html>
            <head>
                <xsl:apply-templates select="name" mode="title"/>
                <link rel="stylesheet" type="text/css">
                    <xsl:attribute name="href">
                        <xsl:call-template name="basePath">
                            <xsl:with-param name="className" select="name"/> 
                        </xsl:call-template>
                        <xsl:text>panda-master.css</xsl:text>
                    </xsl:attribute>
                </link>
                <link rel="stylesheet" type="text/css">
                    <xsl:attribute name="href">
                        <xsl:call-template name="basePath">
                            <xsl:with-param name="className" select="name"/> 
                        </xsl:call-template>
                        <xsl:text>pandadoc.css</xsl:text>
                    </xsl:attribute>
                </link>
                <script>
                    <xsl:attribute name="src">
                        <xsl:call-template name="basePath">
                            <xsl:with-param name="className" select="name"/> 
                        </xsl:call-template>
                        <xsl:text>scripts/site.js</xsl:text>
                    </xsl:attribute>
                </script>
            </head>
            <body>
                <div id="main">
                    <xsl:call-template name="toc">
                        <xsl:with-param name="base">
                            <xsl:text>../</xsl:text>
                            <xsl:call-template name="basePath">
                                <xsl:with-param name="className" select="name"/> 
                            </xsl:call-template>
                        </xsl:with-param>
                    </xsl:call-template>
                    <div id="content">
                        <xsl:apply-templates select="." mode="header"/>
                        <xsl:apply-templates select="ancestors"/>
                        <xsl:apply-templates select="interfaces"/>
                        <div class="classDescription">
                        <xsl:apply-templates select="doc/description"/>
                        </div>

                        <xsl:if test="count(field[count(annotations/annotation[text() = '@class']) > 0]) > 0">
                            <h2>Constant Summary</h2>
                            <dl class="summary">
                                <xsl:apply-templates select="field[count(annotations/annotation[text() = '@class']) > 0]" mode="summary"/>
                            </dl>
                        </xsl:if>
                        <xsl:if test="count((method|function)[count(annotations/annotation[text() = '@class']) > 0]) > 0">
                            <h2>Class Method Summary</h2>
                            <dl class="summary">
                                <xsl:apply-templates select="(method|function)[count(annotations/annotation[text() = '@class']) > 0]" mode="summary"/>
                            </dl>
                        </xsl:if>
                        <xsl:if test="count(constructor) > 0">
                            <h2>Constructor Summary</h2>
                            <dl class="summary">
                                <xsl:apply-templates select="constructor" mode="summary"/>
                            </dl>
                        </xsl:if>
                        <xsl:if test="count(field[count(annotations/annotation[text() = '@class']) = 0]) > 0">
                            <h2>Field Summary</h2>
                            <dl class="summary">
                                <xsl:apply-templates select="field[count(annotations/annotation[text() = '@class']) = 0]" mode="summary"/>
                            </dl>
                        </xsl:if>
                        <xsl:apply-templates select="inheritedFields"/>
                        <xsl:if test="count((method|function)[count(annotations/annotation[text() = '@class']) = 0]) > 0">
                            <h2>Instance Method Summary</h2>
                            <dl class="summary">
                                <xsl:apply-templates select="(method|function)[count(annotations/annotation[text() = '@class']) = 0]" mode="summary"/>
                            </dl>
                        </xsl:if>
                        <xsl:apply-templates select="inheritedMethods"/>
                        <xsl:if test="count(field[count(annotations/annotation[text() = '@class']) > 0]) > 0">
                            <h2>Constants</h2>
                            <xsl:apply-templates select="field[count(annotations/annotation[text() = '@class']) > 0]"/>
                        </xsl:if>
                        <xsl:if test="count(constructor) > 0">
                            <h2>Constructors</h2>
                            <xsl:apply-templates select="constructor"/>
                        </xsl:if>
                        <xsl:if test="count(field[count(annotations/annotation[text() = '@class']) = 0]) > 0">
                            <h2>Fields</h2>
                            <xsl:apply-templates select="field[count(annotations/annotation[text() = '@class']) = 0]"/>
                        </xsl:if>
                        <xsl:if test="count((method|function)[count(annotations/annotation[text() = '@class']) > 0]) > 0">
                            <h2>Class Methods</h2>
                            <xsl:apply-templates select="(method|function)[count(annotations/annotation[text() = '@class']) > 0]"/>
                        </xsl:if>
                        <xsl:if test="count((method|function)[count(annotations/annotation[text() = '@class']) = 0]) > 0">
                            <h2>Instance Methods</h2>
                            <xsl:apply-templates select="(method|function)[count(annotations/annotation[text() = '@class']) = 0]"/>
                        </xsl:if>
                    </div>
                </div>
            </body>
        </html>
    </xsl:template>
    
    <xsl:template match="class/name" mode="title">
        <title>
            <xsl:choose>
                <xsl:when test="../@type = 'interface'">
                    <xsl:text>Interface </xsl:text>
                </xsl:when>
                <xsl:otherwise>Class </xsl:otherwise>
            </xsl:choose>
            <xsl:apply-templates/>
        </title>
    </xsl:template>
    
    <xsl:template match="class" mode="header">
        <xsl:variable name="package">
            <xsl:call-template name="packageName">
                <xsl:with-param name="name" select="name"/>
            </xsl:call-template>
        </xsl:variable>
        <xsl:if test="$package != ''">
            <strong>
                <xsl:text>Package </xsl:text>
                <xsl:value-of select="$package"/>
            </strong>
        </xsl:if>
        <h1>
            <xsl:choose>
                <xsl:when test="@type = 'interface'">
                    <xsl:text>Interface </xsl:text>
                </xsl:when>
                <xsl:otherwise>Class </xsl:otherwise>
            </xsl:choose>
            <xsl:value-of select="simpleName"/>
        </h1>
    </xsl:template>

    <xsl:template match="ancestors/type" mode="indent">
        <xsl:text>&#xa0;&#xA0;&#xa0;&#xA0;</xsl:text>
    </xsl:template>

    <xsl:template match="ancestors/type">
        <div class="ancestor">
            <xsl:apply-templates select="preceding-sibling::type" mode="indent"/>
            &#xa0;&#xA0;&#xa0;&#xA0;&#x2514;        
            <xsl:variable name="href">
                <xsl:apply-templates select="." mode="href"/>
            </xsl:variable>
            <a href="{$href}">
                <xsl:apply-templates select="simpleName"/>
            </a>
        </div>
    </xsl:template>
    
    <xsl:template match="ancestors">
        <p><xsl:apply-templates/></p>
    </xsl:template>

    <xsl:template match="interfaces">
        <div class="minorSectionTitle">
            Implemented Interfaces:
        </div>
        <div class="minorSection">
            <xsl:apply-templates select="type" mode="interface"/>
        </div>
    </xsl:template>

    <xsl:template match="field" mode="summary">
        <dt>
            <a href="#{name}">
                <b><xsl:apply-templates select="name"/></b>
                <xsl:text>:</xsl:text>
                <xsl:apply-templates select="type" mode="simple"/>
            </a>
        </dt>
        <dd>
            <xsl:apply-templates select="doc/description"/>
        </dd>
    </xsl:template>

    <xsl:template match="field">
        <div class="field">
            <div class="fieldHeader">
                <xsl:apply-templates select="annotations"/>
                <a name="{name}" />
                <xsl:choose>
                    <xsl:when test="annotations/annotation[text()='@class']">
                        <xsl:text>constant </xsl:text>
                    </xsl:when>
                    <xsl:when test="annotations/annotation[text()='@final']">
                        <xsl:text>def </xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>var </xsl:text>
                    </xsl:otherwise>
                </xsl:choose>
                <b><xsl:apply-templates select="name"/></b>
                <xsl:text>:</xsl:text>
                <xsl:apply-templates select="type"/>
            </div>
            <div class="fieldBody">
                <xsl:apply-templates select="doc/description"/>
            </div>
        </div>
    </xsl:template>

    <xsl:template name="hint">
        <xsl:param name="operator"/>
        -- <xsl:value-of select="$operator"/> --<br/>
    </xsl:template>
    
    <xsl:template match="name" mode="hint">
        <xsl:choose>
            <xsl:when test=". = '+'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">add operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '-'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">subtract operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '*'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">multiply operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '/'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">divide operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '^'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">exponent operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '='">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">equals operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&gt;'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">greater than operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&lt;'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">less than operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&gt;='">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">greater than or equal operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&lt;='">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">less than or equal operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&amp;'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">logical and operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '|'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">logical or operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '~'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">logical exclusive or operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '!'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">not operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '&amp;&amp;'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">bitwise and operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '||'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">bitwise or operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '~~'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">bitwise exclusive or operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '!!'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">bitwise not operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '[]'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">index operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '[]:='">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">indexed assignment operator</xsl:with-param>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test=". = '->>'">
                <xsl:call-template name="hint">
                    <xsl:with-param name="operator">
                        <xsl:text>conversion from </xsl:text>
                        <xsl:choose>
                            <xsl:when test="count(../params/param) = 1">
                                <xsl:value-of select="../params/param/type/simpleName"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="../../name"/>
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text> to </xsl:text>
                        <xsl:apply-templates select="../return/type"/>
                    </xsl:with-param>
                </xsl:call-template>
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    <xsl:template match="method|function|field" mode="inherited">
        <xsl:if test="count(preceding-sibling::*) > 0">, </xsl:if>
        <a href="{link}"><xsl:value-of select="name"/></a>
    </xsl:template>

    <xsl:template match="method|constructor|function" mode="summary">
        <dt>
            <code>
                <xsl:variable name="hint">
                    <xsl:apply-templates select="name" mode="hint"/>
                </xsl:variable>
                <xsl:if test="$hint != ''">
                    <xsl:value-of select="$hint"/>
                    <br/>
                </xsl:if>
                <b>
                    <a>
                        <xsl:attribute name="href">
                            <xsl:text>#</xsl:text>
                            <xsl:apply-templates select="name"/>
                            <xsl:text>(</xsl:text>
                            <xsl:apply-templates select="params/param" mode="link"/>
                            <xsl:text>)</xsl:text>
                            <xsl:apply-templates select="return" mode="link"/>
                        </xsl:attribute>
                        <xsl:apply-templates select="name"/>
                    </a>
                </b>
                <xsl:text>(</xsl:text>
                <xsl:apply-templates select="params/param"/>
                <xsl:text>)</xsl:text>
                <xsl:apply-templates select="return"/>
            </code>
        </dt>
        <dd>
            <xsl:apply-templates select="doc/summary"/>
        </dd>
    </xsl:template>

    <xsl:template match="method|constructor|function">
        <a>
            <xsl:attribute name="name">
                <xsl:apply-templates select="name"/>
                <xsl:text>(</xsl:text>
                <xsl:apply-templates select="params/param" mode="link"/>
                <xsl:text>)</xsl:text>
                <xsl:apply-templates select="return" mode="link"/>
            </xsl:attribute>
        </a>
        <div class="method">
            <div class="methodHeader">
                <code>
                    <xsl:apply-templates select="name" mode="hint"/>
                    <xsl:apply-templates select="annotations"/>
                    <table cellspacing="0" cellpadding="0" border="0">
                        <tr>
                            <td valign="top" nowrap="nowrap">
                                <xsl:choose>
                                    <xsl:when test="name() = 'constructor'">
                                        <span class="methodName">
                                            <xsl:value-of select="name()"/>
                                        </span>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="name()"/>
                                        <xsl:text> </xsl:text>
                                        <span class="methodName">
                                            <xsl:apply-templates select="name"/>
                                        </span>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </td>
                            <td>
                                <xsl:text>(</xsl:text>
                                <xsl:if test="count(params/param) > 0">
                                    <xsl:apply-templates select="params/param" mode="table"/>
                                    <xsl:if test="return/type/name != 'void'">
                                        <br/>
                                    </xsl:if>
                                </xsl:if>
                                <xsl:text>)</xsl:text>
                                <xsl:apply-templates select="return"/>
                            </td>
                        </tr>
                    </table>
                </code>
            </div>
            <div class="methodBody">
                <div class="methodDescription">
                    <xsl:apply-templates select="doc/description"/>
                    <xsl:apply-templates select="params" mode="description"/>
                    <xsl:apply-templates select="annotations" mode="pre"/>
                    <xsl:apply-templates select="return/description"/>
                    <xsl:apply-templates select="annotations" mode="post"/>
                    <xsl:apply-templates select="seeAlsos"/>
                </div>
            </div>
        </div>
    </xsl:template>
    
    <xsl:template match="param">
        <xsl:if test="position() > 1">
            <xsl:text>, </xsl:text>
        </xsl:if>
        <xsl:apply-templates select="name"/>
        <xsl:text>:</xsl:text>
        <xsl:apply-templates select="type" mode="simple"/>
    </xsl:template>
    
    <xsl:template match="param" mode="link">
        <xsl:if test="position() > 1">
            <xsl:text>,</xsl:text>
        </xsl:if>
        <xsl:apply-templates select="type" mode="link"/>
    </xsl:template>
    
    <xsl:template match="param" mode="table">
        <xsl:if test="position() > 1">
            <xsl:text>,</xsl:text><br/><xsl:text>&#xA0;</xsl:text>
        </xsl:if>
        <xsl:apply-templates select="name"/>
        <xsl:text>:</xsl:text>
        <xsl:apply-templates select="type"/>
    </xsl:template>

    <xsl:template match="params" mode="description">
        <xsl:if test="count(param) > 0">
            <dl>
                <dt><b>Parameters:</b></dt>
                <dd><xsl:apply-templates mode="description"/></dd>
            </dl>
        </xsl:if>
    </xsl:template>
    
    <xsl:template match="param" mode="description">
        <code><xsl:apply-templates select="name"/></code>
        <xsl:text> - </xsl:text>
        <xsl:choose>
            <xsl:when test="description">
                <xsl:apply-templates select="description"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>value of type </xsl:text>
                <code><xsl:apply-templates select="type"/></code>
            </xsl:otherwise>
        </xsl:choose>
        <br/>
    </xsl:template>

    <xsl:template match="annotation">
        <xsl:if test="text() != '@external' and text() != '@math(overflow)'">
            <xsl:apply-templates/>
            <br/>
        </xsl:if>
    </xsl:template>

    <xsl:template match="annotations">
        <xsl:apply-templates select="annotation"/>
    </xsl:template>

    <xsl:template match="annotations" mode="pre">
        <xsl:if test="count(pre/text()) > 0">
            <dl>
                <dt><b>Preconditions:</b></dt>
                <dd><code><xsl:apply-templates select="pre/text()"/></code></dd>
            </dl>
        </xsl:if>
    </xsl:template>

    <xsl:template match="annotations" mode="post">
        <xsl:if test="count(post/text()) > 0">
            <dl>
                <dt><b>Postconditions:</b></dt>
                <dd><code><xsl:apply-templates select="post/text()"/></code></dd>
            </dl>
        </xsl:if>
    </xsl:template>

    <xsl:template match="return">
        <xsl:if test="type != 'void'">
            <xsl:text>:</xsl:text>
            <xsl:apply-templates select="type" mode="simple"/>
        </xsl:if>
    </xsl:template>
    
    <xsl:template match="return" mode="link">
        <xsl:if test="type != 'void'">
            <xsl:text>:</xsl:text>
            <xsl:apply-templates select="type" mode="link"/>
        </xsl:if>
    </xsl:template>
    
    <xsl:template match="return/description">
        <dl>
            <dt><b>Returns:</b></dt>
            <dd><xsl:apply-templates/></dd>
        </dl>
    </xsl:template>

    <xsl:template match="type" mode="href">
        <xsl:variable name="baseDepth">
            <xsl:call-template name="countSubstrings">
                <xsl:with-param name="haystack" select="/class/name"/>
                <xsl:with-param name="needle" select="'.'"/>
            </xsl:call-template>
        </xsl:variable>
        <xsl:call-template name="repeatString">
            <xsl:with-param name="text" select="'../'"/>
            <xsl:with-param name="count" select="$baseDepth"/>
        </xsl:call-template>
        <xsl:variable name="typeName">
            <xsl:call-template name="baseName">
                <xsl:with-param name="name">
                    <xsl:call-template name="replaceString">
                        <xsl:with-param name="haystack" select="name"/>
                        <xsl:with-param name="needle" select="'?'"/>
                        <xsl:with-param name="replacement" select="''"/>
                    </xsl:call-template>
                </xsl:with-param>
            </xsl:call-template>
        </xsl:variable>
        <xsl:call-template name="replaceString">
            <xsl:with-param name="haystack" select="$typeName"/>
            <xsl:with-param name="needle" select="'.'"/>
            <xsl:with-param name="replacement" select="'/'"/>
        </xsl:call-template>
        <xsl:text>.html</xsl:text>
    </xsl:template>

    <xsl:template match="type" name="type">
        <xsl:variable name="href">
            <xsl:apply-templates select="." mode="href"/>
        </xsl:variable>
        <a href="{$href}">
            <xsl:apply-templates select="simpleName"/>
        </a>
    </xsl:template>
    
    <xsl:template match="type" mode="link">
        <xsl:apply-templates select="name"/>
    </xsl:template>

    <xsl:template match="type" mode="interface">
        <xsl:if test="count(preceding-sibling::type) > 0">, </xsl:if>
        <xsl:call-template name="type"/>
    </xsl:template>

    <xsl:template match="type" mode="simple">
        <xsl:variable name="href">
            <xsl:apply-templates select="." mode="href"/>
        </xsl:variable>
        <a href="{$href}">
            <xsl:apply-templates select="simpleName"/>
        </a>
    </xsl:template>

    <xsl:template match="seeAlsos">
        <dl>
            <dt><b>See also:</b></dt>
            <dd><xsl:apply-templates/></dd>
        </dl>
    </xsl:template>
    
    <xsl:template match="seeAlso">
        <xsl:apply-templates/>
        <br/>
    </xsl:template>

    <xsl:template match="inheritedMethods">
        <div class="minorSectionTitle">
            Inherited Methods:
        </div>
        <div class="minorSection">
            <xsl:apply-templates select="*" mode="inherited"/>
        </div>
    </xsl:template>

    <xsl:template match="inheritedFields">
        <div class="minorSectionTitle">
            Inherited Fields:
        </div>
        <div class="minorSection">
            <xsl:apply-templates select="*" mode="inherited"/>
        </div>
    </xsl:template>

    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>