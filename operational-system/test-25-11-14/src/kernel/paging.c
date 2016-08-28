#include "paging.h"

typedef struct page_entry {
	int present: 1;
	int read: 1;
	int user: 1;
	int write: 1;
	int cache: 1;
	int accessed: 1;
	int size: 1;
	int ignored: 1;
	int available: 4;
	int frame_base: 20;
} page_entry_t;

typedef struct page_table {
	
	page_entry_t pages[1024];
	
} page_table_t;

typedef struct page_dir {
	
	page_table_t* tables[1024];
	
} page_dir_t;


extern update_directory(page_dir_t*);
extern enable_paging();

void paging() {
	page_dir_t *directory = (page_dir_t*) 0x10000;
	page_table_t *table0 = (page_table_t*) 0x11000;

//	page_dir_t *directory1 = (page_dir_t*) 0x10000;
	page_table_t *table1 = (page_table_t*) 0x12000;

	int i;
	for (i = 0; i < 1024; i++) {
		table0->pages[i].present 	 = 1;
		table0->pages[i].read		 = 1;
		table0->pages[i].user		 = 1;
		table0->pages[i].write		 = 0;
		table0->pages[i].frame_base = i;
		
		if (i % 2 == 0)
		    table1->pages[i].present 	 = 0;
		else
		    table1->pages[i].present 	 = 1;
		table1->pages[i].read		 = 1;
		table1->pages[i].user		 = 1;
		table1->pages[i].write		 = 0;
		table1->pages[i].frame_base = i + 2048;
	}

    int *tmp = (((unsigned int) table0) | 0x07);
    //test(directory->tables[0]);	
	directory->tables[0] = (page_table_t*) tmp;
	
    *tmp = (((unsigned int) table1) | 0x07);
    //test(directory->tables[0]);	
	directory->tables[1] = (page_table_t*) tmp;

	update_directory(directory);
	
	enable_paging();
	
}
