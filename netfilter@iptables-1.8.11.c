#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/iptables.html

char *msgs[] = {
        "[*] Networking support --->                                                [NET]",
        "  Networking options --->",
        "    [*] Network packet filtering framework (Netfilter) --->          [NETFILTER]",
        "      [*] Advanced netfilter configuration                  [NETFILTER_ADVANCED]",
        "      Core Netfilter Configuration --->",
        "        <*/M> Netfilter connection tracking support               [NF_CONNTRACK]",
        "        <*/M> Netfilter Xtables support (required for ip_tables)",
        "                                                        ...  [NETFILTER_XTABLES]",
        "        <*/M>   LOG target support                     [NETFILTER_XT_TARGET_LOG]",
        "      IP: Netfilter Configuration --->",
        "        <*/M> IP tables support (required for filtering/masq/NAT)",
        "                                                          ...  [IP_NF_IPTABLES]",
        "To see how to configure iptables, see:",
        "    " YELLOW "https://www.linuxfromscratch.org/blfs/view/stable/postlfs/iptables.html" RESET,
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "netfilter@iptables-1.8.11"; }
char *getver(void)   { return "1.8.11"; }
char *getdesc(void)  { return "Configure the Linux 2.4 and later kernel packet filtering ruleset"; }
char *getweb(void)   { return "https://www.netfilter.org/projects/iptables"; }

char *
download(void)
{
        CMD("wget https://www.netfilter.org/projects/iptables/files/iptables-1.8.11.tar.xz", return NULL);
        CMD("tar -vxf iptables-1.8.11.tar.xz", return NULL);
        CMD("rm iptables-1.8.11.tar.xz", return NULL);
        return "iptables-1.8.11";
}

int
build(void)
{
        CMD("./configure --prefix=/usr  \
            --disable-nftables \
            --enable-libipq", return 0);
        return make(NULL);
}

int
install(void)
{
        return make("install");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
