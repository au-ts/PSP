#ifndef PSP_VERSION_H
#define PSP_VERSION_H

/*
 * Development build macro definitions
 */
#define CFE_PSP_IMPL_BUILD_NUMBER   73
#define CFE_PSP_IMPL_BUILD_BASELINE "equuleus-rc1"
#define CFE_PSP_BUILD_DEV_CYCLE     "equuleus-rc2" /**< @brief Development: Release name for current development cycle */
#define CFE_PSP_BUILD_CODENAME      "Equuleus" /**< @brief: Development: Code name for the current build */

/*
 * Version macros, see \ref cfsversions for definitions
 */
#define CFE_PSP_IMPL_MAJOR_VERSION 1  /*!< @brief Major version number */
#define CFE_PSP_IMPL_MINOR_VERSION 4  /*!< @brief Minor version number */
#define CFE_PSP_IMPL_REVISION      0  /*!< @brief Revision version number: value of 0 indicates a development version */

/**
 * @brief Last official release
 */
#define CFE_PSP_LAST_OFFICIAL "v1.4.0"

/*!
 * @brief Mission revision
 *
 * Reserved for mission use to denote patches/customizations as needed
 * Values 1-254 are reserved for mission use to denote patches/customizations as needed
 * NOTE: Reserving 0 and 0xFF for cFS open-source development use (pending resolution of nasa/cFS#440)
 */
#define CFE_PSP_IMPL_MISSION_REV 0xFF

#define CFE_PSP_IMPL_STR_HELPER(x) #x
#define CFE_PSP_IMPL_STR(x) CFE_PSP_IMPL_STR_HELPER(x)

/*!
 * @brief Development: Build version number
 * @details Baseline git tag + number of commits since baseline @n
 * See @ref cfsversions for format differences between development and release versions
 */
#define CFE_PSP_IMPL_VERSION CFE_PSP_IMPL_BUILD_BASELINE "+dev" CFE_PSP_IMPL_STR(CFE_PSP_IMPL_BUILD_NUMBER)

/**
 * @brief Max version string length
 *
 * Maximum length that a tblCRCTool version string can be
 */
#define CFE_PSP_CFG_MAX_VERSION_STR_LEN 256

#endif
