#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* This file constructs a new configuration in memory and writes it to
 * 'config.cfg.'
 */

int main(int argc, char **argv)
{
  static const char *output_file = "config.conf";
  FILE *file;

  config_t cfg;
  config_setting_t *root, *path_setting, *buffsize_setting, *setting, *group, *list,
    *inner_list, *group_2, *group_3, *group_4, *group_5;

  char columns[50];
  char join_left_column[50];
  char join_right_column[50];
  char left_table_name[50];
  char line[256];
  char right_table_name[50];
  char sql_operation[50];

  char *colon;
  char *table_name = "";
  char *table_name_2 = "";
  char *value;

  int i;
  int index_of_colon;
  int isJoin = FALSE;

  file = fopen("sample_query.txt", "r");
  while (fgets(line, sizeof(line), file)) {
      memset(&sql_operation[0], 0, sizeof(sql_operation));

      colon = strchr(line, ':');
      index_of_colon = (int)(colon - line);
      strncpy(sql_operation, line, index_of_colon);

      // printf("entire line: %s", line);
      // printf("sql operation: %s\n", sql_operation);

      value = strstr(line, ":");
      if (value != NULL) {
        // printf("value: %s\n", value + 2);
      } else {
        // printf("\n\n");
      }

      if (strcmp("columns", sql_operation) == 0) {
          // printf("COLUMNS\n");
          strncpy(columns, value + 2, strlen(value));
      } else if (strcmp("table", sql_operation) == 0) {
          // printf("TABLE\n");
          if (strlen(left_table_name) == 0) {
            strncpy(left_table_name, value + 2, strlen(value));
          } else {
            strncpy(right_table_name, value + 2, strlen(value));
          }
      } else if (strcmp("join", sql_operation) == 0) {
        isJoin = TRUE;
      } else if (strcmp("on", sql_operation) == 0) {
          // printf("VALUE: %s", value + 2);
          if (strlen(join_left_column) == 0) {
            strncpy(join_left_column, value + 2, strlen(value));
          } else {
            strncpy(join_right_column, value, strlen(value));            
          }
      }
  }

  config_init(&cfg);
  root = config_root_setting(&cfg);

  path_setting = config_setting_add(root, "path", CONFIG_TYPE_STRING);
  config_setting_set_string(path_setting, "drivers/sample_queries/data/");

  buffsize_setting = config_setting_add(root, "buffsize", CONFIG_TYPE_INT);
  config_setting_set_int(buffsize_setting, 1048576);

  // Add node configs here. They are groups.

  if (strcmp("lineitem\n", left_table_name) == 0) {
    group = config_setting_add(root, "scanL", CONFIG_TYPE_GROUP);
    table_name = "scanL"; 
    
    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "lineitem.tbl.bz2");

    setting = config_setting_add(group, "verbose", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "true");

    // MAPPING.
    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "dec");
  } else if (strcmp("nation\n", left_table_name) == 0) { 
    group = config_setting_add(root, "scanN", CONFIG_TYPE_GROUP);
    table_name = "scanN";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "nation.tbl");

    setting = config_setting_add(group, "verbose", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "true");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }
    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "string");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    // schema = ( figure it out );
  } else if (strcmp("order\n", left_table_name) == 0) {
    group = config_setting_add(root, "scanO", CONFIG_TYPE_GROUP);
    table_name = "scanO";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "order.tbl.bz2");
  
    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
  } else if (strcmp("part\n", left_table_name) == 0) {
    group = config_setting_add(root, "scanP", CONFIG_TYPE_GROUP);
    table_name = "scanP";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "part.tbl.bz2");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "dec");

  } else if (strcmp("region\n", left_table_name) == 0) {
    group = config_setting_add(root, "scanR", CONFIG_TYPE_GROUP);
    table_name = "scanR";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "region.tbl");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "string");
  } else {
    printf("ERROR: table name not recognized.\n");
  }


  if (strcmp("lineitem\n", right_table_name) == 0) {
    group = config_setting_add(root, "scanL", CONFIG_TYPE_GROUP);
    table_name_2 = "scanL";
    
    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "lineitem.tbl.bz2");

    setting = config_setting_add(group, "verbose", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "true");

    // MAPPING.
    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "dec");
  } else if (strcmp("nation\n", right_table_name) == 0) { 
    group = config_setting_add(root, "scanN", CONFIG_TYPE_GROUP);
    table_name_2 = "scanN";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "nation.tbl");

    setting = config_setting_add(group, "verbose", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "true");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }
    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "string");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    // schema = ( figure it out );
  } else if (strcmp("order\n", right_table_name) == 0) {
    group = config_setting_add(root, "scanO", CONFIG_TYPE_GROUP);
    table_name_2 = "scanO";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "order.tbl.bz2");
  
    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
  } else if (strcmp("part\n", right_table_name) == 0) {
    group = config_setting_add(root, "scanP", CONFIG_TYPE_GROUP);
    table_name_2 = "scanP";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "part.tbl.bz2");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "dec");

  } else if (strcmp("region\n", right_table_name) == 0) {
    group = config_setting_add(root, "scanR", CONFIG_TYPE_GROUP);
    table_name_2 = "scanR";

    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "parallelscan");

    setting = config_setting_add(group, "filetype", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "text");

    setting = config_setting_add(group, "files", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "region.tbl");

    list = config_setting_add(group, "mapping", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    for(i = 0; i < 4; ++i)
    {
      setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    // SCHEMA.
    list = config_setting_add(group, "schema", CONFIG_TYPE_LIST);
    inner_list = config_setting_add(list, NULL, CONFIG_TYPE_LIST);
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "long");
    setting = config_setting_add(inner_list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "string");
  } else {
    printf("ERROR: table name not recognized.\n");
  }

  if (isJoin) {
    // Get right table name.
    group = config_setting_add(root, "joinTable", CONFIG_TYPE_GROUP);
    setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "hashjoin");

    group_2 = config_setting_add(group, "hash", CONFIG_TYPE_GROUP);
    setting = config_setting_add(group_2, "fn", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "modulo");

    list = config_setting_add(group_2, "range", CONFIG_TYPE_ARRAY);
    setting = config_setting_add(list, NULL, CONFIG_TYPE_INT);
    config_setting_set_int(setting, 1);
    setting = config_setting_add(list, NULL, CONFIG_TYPE_INT);
    config_setting_set_int(setting, 800000);

    setting = config_setting_add(group_2, "buckets", CONFIG_TYPE_INT);
    config_setting_set_int(setting, 262144);

    setting = config_setting_add(group, "tuplesperbucket", CONFIG_TYPE_INT);
    config_setting_set_int(setting, 4);
    setting = config_setting_add(group, "buildjattr", CONFIG_TYPE_INT);
    config_setting_set_int(setting, 0);
    setting = config_setting_add(group, "probejattr", CONFIG_TYPE_INT);
    config_setting_set_int(setting, 1);

    list = config_setting_add(group, "projection", CONFIG_TYPE_LIST);
    setting = config_setting_add(list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "B$1");
    setting = config_setting_add(list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "P$0");
    setting = config_setting_add(list, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "P$2");

    list = config_setting_add(group, "threadgroups", CONFIG_TYPE_LIST);
    for (i = 0; i < 4; i++) {
      setting = config_setting_add(list, NULL, CONFIG_TYPE_INT);
      config_setting_set_int(setting, i);
    }

    setting = config_setting_add(group, "allocpolicy", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "striped");
  }

  group = config_setting_add(root, "eval", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, "q1eval");

  group = config_setting_add(root, "cycleaccountant", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group, "type", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, "cycle_accountant");

  // Add treeroot configs here. They are nested groups. 
  group = config_setting_add(root, "treeroot", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, "cycleaccountant");

  group_2 = config_setting_add(group, "input", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group_2, "name", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, "joinTable");

  group_3 = config_setting_add(group_2, "build", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group_3, "name", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, table_name);

  group_4 = config_setting_add(group_2, "probe", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group_4, "name", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, "cycleaccountant");

  group_5 = config_setting_add(group_4, "input", CONFIG_TYPE_GROUP);
  setting = config_setting_add(group_5, "name", CONFIG_TYPE_STRING);
  config_setting_set_string(setting, table_name_2);

  /* Write out the new configuration. */
  if(! config_write_file(&cfg, output_file))
  {
    fprintf(stderr, "Error while writing file.\n");
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }

  fprintf(stderr, "New configuration successfully written to: %s\n",
          output_file);

  config_destroy(&cfg);
  fclose(file);

  return(EXIT_SUCCESS);
}
/* eof */
