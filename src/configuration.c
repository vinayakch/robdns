#include "configuration.h"
#include "conf-trackfile.h"
#include <string.h>
#include <stdlib.h>


/****************************************************************************
 ****************************************************************************/
struct Configuration *cfg_create(void)
{
    struct Configuration *cfg;

    cfg = malloc(sizeof(*cfg));
    memset(cfg, 0, sizeof(cfg[0]));

    cfg->zone_defaults = malloc(sizeof(*cfg->zone_defaults));
    memset(cfg->zone_defaults, 0, sizeof(*cfg->zone_defaults));

    /* Create a subsystem that keeps track of all the configuration files */
    cfg->tf = conf_trackfile_create();
    return cfg;
}

/****************************************************************************
 ****************************************************************************/
void
free2(char *str)
{
    if (str)
        free(str);
}

/****************************************************************************
 ****************************************************************************/
void cfg_destroy(struct Configuration *cfg)
{
    if (cfg == NULL)
        return;

    free2(cfg->options.directory);
    free2(cfg->options.pid_file);
    free2(cfg->options.hostname);
    free2(cfg->options.server_id);
    free2(cfg->options.version);

    free(cfg);
}


int
cfg_selftest(void)
{
    struct Configuration *cfg;

    cfg = cfg_create();

    cfg_load_string(cfg, "options {\n listen-on port 53 { any; { 127.0.0.1; ::1; }; }; };");
    
    cfg_destroy(cfg);

    return 0;
}
