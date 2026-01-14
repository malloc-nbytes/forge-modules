#include <forge/forge.h>

char *deps[] = {
        "libarchive@libarchive",
        "GNOME@libxml2",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "dockbook@dockbook-xml-4.5.0"; }
char *getver(void)   { return "4.5.0"; }
char *getdesc(void)  { return "type definitions for verification of XML data files against the DocBook rule set"; }
char *getweb(void)   { return "https://docbook.org/"; }

char *
download(void)
{
        CMD("wget https://www.docbook.org/xml/4.5/docbook-xml-4.5.zip", return NULL);
        if (!mkdirp("docbook-xml-4.5")) return NULL;
        CMD("mv docbook-xml-4.5.zip docbook-xml-4.5", {
                cmd("rm docbook-xml-4.5");
                return NULL;
        });
        CD("docbook-xml-4.5", {
                cmd("rm docbook-xml-4.5");
                return NULL;
        });
        CMD("unzip docbook-xml-4.5.zip", {
                cd("..");
                cmd("rm docbook-xml-4.5");
                return NULL;
        });
        (void)cmd("rm docbook-xml-4.5.zip");
        return "docbook-xml-4.5";
}

int
install(void)
{
        CMD("install -v -d -m755 $DESTDIR/usr/share/xml/docbook/xml-dtd-4.5", return 0);
        CMD("install -v -d -m755 $DESTDIR/etc/xml", return 0);
        CMD("cp -v -af --no-preserve=ownership docbook.cat *.dtd ent/ *.mod \
                     $DESTDIR/usr/share/xml/docbook/xml-dtd-4.5", return 0);

        // Populate the `/etc/xml/docbook' catalog

        CMD("if [ ! -e /etc/xml/docbook ]; then \
                 xmlcatalog --noout --create $DESTDIR/etc/xml/docbook \
             fi", return 0);

        CMD("xmlcatalog --noout --add \"public\"               \
                \"-//OASIS//DTD DocBook XML V4.5//EN\"         \
                \"http://www.oasis-open.org/docbook/xml/4.5/docbookx.dtd\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                           \
                \"-//OASIS//DTD DocBook XML CALS Table Model V4.5//EN\"    \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/calstblx.dtd\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                           \
                \"-//OASIS//DTD XML Exchange Table Model 19990315//EN\"    \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/soextblx.dtd\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                             \
                \"-//OASIS//ELEMENTS DocBook XML Information Pool V4.5//EN\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/dbpoolx.mod\"    \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                               \
                \"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.5//EN\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/dbhierx.mod\"      \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                           \
                \"-//OASIS//ELEMENTS DocBook XML HTML Tables V4.5//EN\"    \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/htmltblx.mod\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                          \
                \"-//OASIS//ENTITIES DocBook XML Notations V4.5//EN\"     \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/dbnotnx.mod\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                               \
                \"-//OASIS//ENTITIES DocBook XML Character Entities V4.5//EN\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/dbcentx.mod\"      \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"public\"                                        \
                \"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.5//EN\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5/dbgenent.mod\"              \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"rewriteSystem\"       \
                \"http://www.oasis-open.org/docbook/xml/4.5\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5\" \
                $DESTDIR/etc/xml/docbook", return 0);

        CMD("xmlcatalog --noout --add \"rewriteURI\"          \
                \"http://www.oasis-open.org/docbook/xml/4.5\" \
                \"file:///usr/share/xml/docbook/xml-dtd-4.5\" \
                $DESTDIR/etc/xml/docbook", return 0);

        // Populate the `/etc/xml/catalog'

        CMD("if [ ! -e $DESTDIR/etc/xml/catalog ]; then \
                xmlcatalog --noout --create $DESTDIR/etc/xml/catalog \
             fi", return 0);

        CMD("xmlcatalog --noout --add \"delegatePublic\" \
                \"-//OASIS//ENTITIES DocBook XML\"       \
                \"file:///etc/xml/docbook\"              \
                $DESTDIR/etc/xml/catalog", return 0);

        CMD("xmlcatalog --noout --add \"delegatePublic\" \
                \"-//OASIS//DTD DocBook XML\"            \
                \"file:///etc/xml/docbook\"              \
                $DESTDIR/etc/xml/catalog", return 0);

        CMD("xmlcatalog --noout --add \"delegateSystem\" \
                \"http://www.oasis-open.org/docbook/\"   \
                \"file:///etc/xml/docbook\"              \
                $DESTDIR/etc/xml/catalog", return 0);

        CMD("xmlcatalog --noout --add \"delegateURI\"    \
                \"http://www.oasis-open.org/docbook/\"   \
                \"file:///etc/xml/docbook\"              \
                $DESTDIR/etc/xml/catalog", return 0);

        const char *config = "for DTDVERSION in 4.1.2 4.2 4.3 4.4\n"
                "do\n"
                "  xmlcatalog --noout --add \"public\"                                  \\"
                "    \"-//OASIS//DTD DocBook XML V$DTDVERSION//EN\"                     \\"
                "    \"http://www.oasis-open.org/docbook/xml/$DTDVERSION/docbookx.dtd\" \\"
                "    $DESTDIR/etc/xml/docbook"
                "\n"
                "  xmlcatalog --noout --add \"rewriteSystem\"              \\"
                "    \"http://www.oasis-open.org/docbook/xml/$DTDVERSION\" \\"
                "    \"file:///usr/share/xml/docbook/xml-dtd-4.5\"         \\"
                "    $DESTDIR/etc/xml/docbook"
                "\n"
                "  xmlcatalog --noout --add \"rewriteURI\"                 \\"
                "    \"http://www.oasis-open.org/docbook/xml/$DTDVERSION\" \\"
                "    \"file:///usr/share/xml/docbook/xml-dtd-4.5\"         \\"
                "    $DESTDIR/etc/xml/docbook"
                "\n"
                "  xmlcatalog --noout --add \"delegateSystem\"              \\"
                "    \"http://www.oasis-open.org/docbook/xml/$DTDVERSION/\" \\"
                "    \"file:///etc/xml/docbook\"                            \\"
                "    $DESTDIR/etc/xml/catalog"
                "\n"
                "  xmlcatalog --noout --add \"delegateURI\"                 \\"
                "    \"http://www.oasis-open.org/docbook/xml/$DTDVERSION/\" \\"
                "    \"file:///etc/xml/docbook\"                            \\"
                "    $DESTDIR/etc/xml/catalog"
                "done";
        return cmd(config);
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
