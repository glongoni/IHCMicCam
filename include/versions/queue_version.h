/*
 * Revisão do último commit desta lib/entidade: 2531
 * Data do último commit desta lib/entidade: 2010/11/03 17:13:25
 * Range do último commit: 2549
 * URL: https://143.54.132.132/svn/iva/branches/v1.6.x/src/queue
 * Data de geração deste arquivo: 2010/11/18 12:42:51
 */
 
#ifndef _SW_VERSION_H_
#define _SW_VERSION_H_

// numeração das versões segue o padrão: major.stable.minor.revision
// Major: major version
// Stable: segundo número de versão, modificado quando uma versão fica estável
// Minor: minor version -- quando incluídas funcionalidades, corrigidos bugs, etc.
// Revision: número da revisão da lib/entidade no svn

#define SW_VERSION_MAJOR        1                   ///< Versão geral
#define SW_VERSION_COMPAT       5                   ///< Versão compatibilidade
#define SW_VERSION_MINOR        6                   ///< Versão secundária
#define SW_VERSION_REV          2531             ///< Versão SVN
#define SW_VERSION_TYPE         dev               ///< Tipo do release: "dev" quando versão em desenvolvimento
#define SW_VERSION_STR_4        "1.5.6b.2531-dev"     ///< String com nome inteiro da versão
#define SW_VERSION_STR_3        "1.5.6"             ///< String com nome da versão simplificada (apenas numérica)

#endif

