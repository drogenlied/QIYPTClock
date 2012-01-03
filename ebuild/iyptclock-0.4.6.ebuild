# Copyright 1999-2011 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="2"

inherit eutils qt4-r2

DESCRIPTION="Qt4-Clock originally written for 25th IYPT2012"
HOMEPAGE="http://iypt.de/"
SRC_URI="http://intern.sfz-bw.de/~simeon.voelkel/gentoo/${P}.tar.bz2"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

DEPEND="x11-libs/qt-gui:4
dev-cpp/tclap"

S=${WORKDIR}/${MY_P}

src_configure() {
	eqmake4 iyptclock.pro PREFIX="${D}"/usr || die
	cd iyptclockclient
	eqmake4 iyptclockclient.pro PREFIX="${D}"/usr || die
#	cd ../multiclockclient
#	eqmake4 multiclockclient.pro PREFIX="${D}"/usr || die
	cd ..
}

src_compile() {
	make || die
	cd iyptclockclient
	make || die
#	cd ../multiclockclient
#	make || die
	cd ..
}

src_install() {
	dobin iyptclock
	cd iyptclockclient
	dobin iyptclockclient
#	cd ../multiclockclient
#	dobin multiclockclient
	cd ..
	insinto /usr/share/iyptclock
	doins stages.txt
}

