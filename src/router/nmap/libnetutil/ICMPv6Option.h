
/***************************************************************************
 * ICMPv6Option.h -- The ICMPv6Option Class represents an ICMP version 6   *
 * option. It contains methods to set any header field. In general, these  *
 * methods do error checkings and byte order conversion.                   *
 *                                                                         *
 ***********************IMPORTANT NMAP LICENSE TERMS************************
 *                                                                         *
 * The Nmap Security Scanner is (C) 1996-2012 Insecure.Com LLC. Nmap is    *
 * also a registered trademark of Insecure.Com LLC.  This program is free  *
 * software; you may redistribute and/or modify it under the terms of the  *
 * GNU General Public License as published by the Free Software            *
 * Foundation; Version 2 with the clarifications and exceptions described  *
 * below.  This guarantees your right to use, modify, and redistribute     *
 * this software under certain conditions.  If you wish to embed Nmap      *
 * technology into proprietary software, we sell alternative licenses      *
 * (contact sales@insecure.com).  Dozens of software vendors already       *
 * license Nmap technology such as host discovery, port scanning, OS       *
 * detection, version detection, and the Nmap Scripting Engine.            *
 *                                                                         *
 * Note that the GPL places important restrictions on "derived works", yet *
 * it does not provide a detailed definition of that term.  To avoid       *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * "derivative work" for the purpose of this license if it does any of the *
 * following:                                                              *
 * o Integrates source code from Nmap                                      *
 * o Reads or includes Nmap copyrighted data files, such as                *
 *   nmap-os-db or nmap-service-probes.                                    *
 * o Executes Nmap and parses the results (as opposed to typical shell or  *
 *   execution-menu apps, which simply display raw Nmap output and so are  *
 *   not derivative works.)                                                *
 * o Integrates/includes/aggregates Nmap into a proprietary executable     *
 *   installer, such as those produced by InstallShield.                   *
 * o Links to a library or executes a program that does any of the above   *
 *                                                                         *
 * The term "Nmap" should be taken to also include any portions or derived *
 * works of Nmap, as well as other software we distribute under this       *
 * license such as Zenmap, Ncat, and Nping.  This list is not exclusive,   *
 * but is meant to clarify our interpretation of derived works with some   *
 * common examples.  Our interpretation applies only to Nmap--we don't     *
 * speak for other people's GPL works.                                     *
 *                                                                         *
 * If you have any questions about the GPL licensing restrictions on using *
 * Nmap in non-GPL works, we would be happy to help.  As mentioned above,  *
 * we also offer alternative license to integrate Nmap into proprietary    *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of Nmap.  Please email sales@insecure.com for     *
 * further information.                                                    *
 *                                                                         *
 * As a special exception to the GPL terms, Insecure.Com LLC grants        *
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two. You must obey the GNU GPL in all *
 * respects for all of the code used other than OpenSSL.  If you modify    *
 * this file, you may extend this exception to your version of the file,   *
 * but you are not obligated to do so.                                     *
 *                                                                         *
 * If you received these files with a written license agreement or         *
 * contract stating terms other than the terms above, then that            *
 * alternative license agreement takes precedence over these comments.     *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes (none     *
 * have been found so far).                                                *
 *                                                                         *
 * Source code also allows you to port Nmap to new platforms, fix bugs,    *
 * and add new features.  You are highly encouraged to send your changes   *
 * to nmap-dev@insecure.org for possible incorporation into the main       *
 * distribution.  By sending these changes to Fyodor or one of the         *
 * Insecure.Org development mailing lists, or checking them into the Nmap  *
 * source code repository, it is understood (unless you specify otherwise) *
 * that you are offering the Nmap Project (Insecure.Com LLC) the           *
 * unlimited, non-exclusive right to reuse, modify, and relicense the      *
 * code.  Nmap will always be available Open Source, but this is important *
 * because the inability to relicense code has caused devastating problems *
 * for other Free Software projects (such as KDE and NASM).  We also       *
 * occasionally relicense the code to third parties as discussed above.    *
 * If you wish to specify special license conditions of your               *
 * contributions, just say so when you send them.                          *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License v2.0 for more details at                         *
 * http://www.gnu.org/licenses/gpl-2.0.html , or in the COPYING file       *
 * included with Nmap.                                                     *
 *                                                                         *
 ***************************************************************************/
/* This code was originally part of the Nping tool.                        */

#ifndef __ICMPv6OPTION_H__
#define __ICMPv6OPTION_H__ 1

#include "NetworkLayerElement.h"

/* Packet header diagrams included in this file have been taken from the
 * following IETF RFC documents: RFC 2461, RFC 2894 */

/* The following codes have been defined by IANA. A complete list may be found
 * at http://www.iana.org/assignments/icmpv6-parameters */

/* ICMPv6 Option Types */
#define ICMPv6_OPTION_SRC_LINK_ADDR 1
#define ICMPv6_OPTION_TGT_LINK_ADDR 2
#define ICMPv6_OPTION_PREFIX_INFO   3
#define ICMPv6_OPTION_REDIR_HDR     4
#define ICMPv6_OPTION_MTU           5

/* Nping ICMPv6Options Class internal definitions */
#define ICMPv6_OPTION_COMMON_HEADER_LEN    2
#define ICMPv6_OPTION_MIN_HEADER_LEN       8
#define ICMPv6_OPTION_SRC_LINK_ADDR_LEN    (ICMPv6_OPTION_COMMON_HEADER_LEN+6)
#define ICMPv6_OPTION_TGT_LINK_ADDR_LEN    (ICMPv6_OPTION_COMMON_HEADER_LEN+6)
#define ICMPv6_OPTION_PREFIX_INFO_LEN      (ICMPv6_OPTION_COMMON_HEADER_LEN+30)
#define ICMPv6_OPTION_REDIR_HDR_LEN        (ICMPv6_OPTION_COMMON_HEADER_LEN+6)
#define ICMPv6_OPTION_MTU_LEN              (ICMPv6_OPTION_COMMON_HEADER_LEN+6)
/* This must the MAX() of all values defined above*/
#define ICMPv6_OPTION_MAX_MESSAGE_BODY     (ICMPv6_OPTION_PREFIX_INFO_LEN-ICMPv6_OPTION_COMMON_HEADER_LEN)

#define ICMPv6_OPTION_LINK_ADDRESS_LEN 6

class ICMPv6Option : public NetworkLayerElement {

    private:

        /**********************************************************************/
        /* COMMON ICMPv6 OPTION HEADER                                        */
        /**********************************************************************/

        struct nping_icmpv6_option{
            u8 type;
            u8 length;
            u8 data[ICMPv6_OPTION_MAX_MESSAGE_BODY];
        }__attribute__((__packed__));
        typedef struct nping_icmpv6_option nping_icmpv6_option_t;

        /**********************************************************************/
        /* ICMPv6 OPTION FORMATS                                              */
        /**********************************************************************/
        /* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
           |     Type      |    Length     |              ...              |
           +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
           ~                              ...                              ~
           +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */


        /* Source/Target Link-layer Address
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |     Type      |    Length     |    Link-Layer Address ...
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
        struct link_addr_option{
            u8 link_addr[6];
        }__attribute__((__packed__));
        typedef struct link_addr_option link_addr_option_t;


        /* Prefix Information
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |     Type      |    Length     | Prefix Length |L|A| Reserved1 |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                         Valid Lifetime                        |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                       Preferred Lifetime                      |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                           Reserved2                           |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                                                               |
          +                                                               +
          |                                                               |
          +                            Prefix                             +
          |                                                               |
          +                                                               +
          |                                                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
        struct prefix_info_option{
            u8 prefix_length;
            u8 flags;
            u32 valid_lifetime;
            u32 preferred_lifetime;
            u32 reserved;
            u8 prefix[16];
        }__attribute__((__packed__));
        typedef struct prefix_info_option prefix_info_option_t;


        /* Redirect Header
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |     Type      |    Length     |            Reserved           |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                           Reserved                            |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                                                               |
          ~                       IP header + data                        ~
          |                                                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
        struct redirect_option{
            u16 reserved_1;
            u32 reserved_2;
            //u8 invoking_pkt[?];
        }__attribute__((__packed__));
        typedef struct redirect_option redirect_option_t;


        /* MTU
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |     Type      |    Length     |           Reserved            |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                              MTU                              |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */
        struct mtu_option{
            u16 reserved;
            u32 mtu;
        }__attribute__((__packed__));
        typedef struct mtu_option mtu_option_t;


        nping_icmpv6_option_t h;

        link_addr_option_t        *h_la;
        prefix_info_option_t      *h_pi;
        redirect_option_t         *h_r;
        mtu_option_t              *h_mtu;

    public:
        ICMPv6Option();
        ~ICMPv6Option();
        void reset();
        u8 *getBufferPointer();
        int storeRecvData(const u8 *buf, size_t len);
        int protocol_id() const;

        int setType(u8 val);
        u8 getType();
        bool validateType(u8 val);

        int setLength(u8 val);
        u8 getLength();

        int setLinkAddress(u8* val);
        u8 *getLinkAddress();

        int setPrefixLength(u8 val);
        u8 getPrefixLength();

        int setFlags(u8 val);
        u8 getFlags();

        int setValidLifetime(u32 val);
        u32 getValidLifetime();

        int setPreferredLifetime(u32 val);
        u32 getPreferredLifetime();

        int setPrefix(u8 *val);
        u8 *getPrefix();

        int setMTU(u32 val);
        u32 getMTU();

        int getHeaderLengthFromType(u8 type);

}; /* End of class ICMPv6Option */

#endif
