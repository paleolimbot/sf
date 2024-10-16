
#include <ogrsf_frmts.h>

#define RCPP_DEFAULT_INCLUDE_CALL false
#include "Rcpp.h"

#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(3,11,0)
#include <gdal_adbc.h>


static uint8_t SfGDALADBCLoadDriver(const char *driver_name,
                                    const char *entrypoint, int version,
                                    void *driver, void *error) {
    Rcpp::Environment pkg = Rcpp::Environment::namespace_env("sf");
    Rcpp::Function loader = pkg["sf_load_adbc"];

    Rcpp::CharacterVector driver_name_sexp(driver_name);
    Rcpp::RObject entrypoint_sexp(R_NilValue);
    if (entrypoint) {
        entrypoint_sexp = Rcpp::CharacterVector(entrypoint);
    }

    Rcpp::IntegerVector version_sexp(version);
    Rcpp::RObject driver_sexp(R_MakeExternalPtr(driver, R_NilValue, R_NilValue));
    Rcpp::RObject error_sexp(R_MakeExternalPtr(driver, R_NilValue, R_NilValue));
    Rcpp::RObject result_sexp = loader(driver_name_sexp, entrypoint_sexp, version_sexp, driver_sexp, error_sexp);
    return Rcpp::as<uint8_t>(result_sexp);
}

#endif


// [[Rcpp::export]]
void CPL_init_adbc() {
#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(3,11,0)
    GDALSetAdbcLoadDriverOverride(&SfGDALADBCLoadDriver);
#endif
}
