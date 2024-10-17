
sf_load_adbc <- function(driver_name, entrypoint, version, driver, error) {
    message("Loading!")
    tryCatch(
        adbcdrivermanager::adbc_driver_load(driver_name, entrypoint, version, driver, error),
        error = function(...) 5L
    )
}
