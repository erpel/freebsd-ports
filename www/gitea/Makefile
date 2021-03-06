# $FreeBSD$

PORTNAME=	gitea
DISTVERSIONPREFIX=	v
DISTVERSION=	1.10.4
CATEGORIES=	www

MAINTAINER=	stb@lassitu.de
COMMENT=	Compact self-hosted Git service

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	git:devel/git

USES=		go:modules
USE_GITHUB=	yes
GH_ACCOUNT=	go-gitea
USE_RC_SUBR=	gitea

GO_BUILDFLAGS=	-tags "${GO_TAGS}" -ldflags '-X "main.Version=${PORTVERSION}"'
GO_TARGET=	:${PREFIX}/sbin/${PORTNAME}

SUB_FILES+=	app.ini.sample
SUB_LIST+=	GITUSER=${USERS}

USERS=		git
GROUPS=		git

OPTIONS_DEFINE=	CERT PAM SQLITE
OPTIONS_DEFAULT=	${OPTIONS_DEFINE}

CERT_DESC=	Automatic creation of self-signed certificates
PAM_DESC=	Authentication using PAM

CERT_VARS=	GO_TAGS+=cert
PAM_VARS=	GO_TAGS+=pam
SQLITE_VARS=	GO_TAGS+="sqlite sqlite_unlock_notify"

.include <bsd.port.options.mk>

.if ${OPSYS} == FreeBSD
DAEMONARGS=	-S -l \$${gitea_facility} -s \$${gitea_priority} -T \$${name}
.else
DAEMONARGS=	-f
.endif

SUB_LIST+=	DAEMONARGS="${DAEMONARGS}"

post-install:
	@${MKDIR} ${STAGEDIR}${ETCDIR}/conf
	${INSTALL_DATA} ${WRKDIR}/app.ini.sample ${STAGEDIR}${ETCDIR}/conf/app.ini.sample
	${INSTALL_DATA} ${GO_WRKSRC}/custom/conf/app.ini.sample ${STAGEDIR}${ETCDIR}/conf/app.ini.defaults
	cd ${GO_WRKSRC} && ${COPYTREE_SHARE} "options public templates" ${STAGEDIR}${DATADIR}

	@${MKDIR} ${STAGEDIR}${DESTDIR}/var/db/${PORTNAME}
	@${MKDIR} ${STAGEDIR}${DESTDIR}/var/log/${PORTNAME}
	@${MKDIR} ${STAGEDIR}${DESTDIR}/var/run/${PORTNAME}

.include <bsd.port.mk>
