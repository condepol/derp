# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

struct time_entry {
  struct timeval timestamp;
  char * name;
};

struct time_log {
  unsigned int entries_counter;
  struct time_entry * entries;
  unsigned int mem_size;
};

void init_time_log(struct time_log * record) {
  record->mem_size = 10;
  record->entries = malloc(record->mem_size*sizeof(struct time_entry));
  record->entries_counter = 0;
}

void free_time_log(struct time_log * record) {
  free(record->entries);
}

void log_time(struct time_log * record, char * name)
{
  /* ajustement de la taille de time_log->entries si nécéssaire */
  if (record->entries_counter == record->mem_size)
  {
    record->entries = realloc(record->entries,(record->mem_size + 10) * sizeof(struct time_entry));
    record->mem_size += 10;
  }
  /* ajout d'une entrée de mesure de temps */
  if (gettimeofday(&(record->entries[record->entries_counter].timestamp),NULL)) {perror("gettimeofday");}
  record->entries[record->entries_counter].name = name;
  record->entries_counter++;
}

void print_times(struct time_log * record)
{
  unsigned int i;
  for (i=0;i<record->entries_counter;i++)
  {
    printf("%d %d %s\n",
      (unsigned int)record->entries[i].timestamp.tv_sec,
      (unsigned int)record->entries[i].timestamp.tv_usec,
      record->entries[i].name
      );
  }
}
