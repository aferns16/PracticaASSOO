#define ASSOOFS_MAGIC 0x20170509
#define ASSOOFS_DEFAULT_BLOCK_SIZE 4096
#define ASSOOFS_FILENAME_MAXLEN 255
#define ASSOOFS_START_INO 10
#define ASSOOFS_RESERVED_INODES 3 
#define ASSOOFS_LAST_RESERVED_BLOCK ASSOOFS_ROOTDIR_DATABLOCK_NUMBER
#define ASSOOFS_LAST_RESERVED_INODE ASSOOFS_INODESTORE_BLOCK_NUMBER
const int ASSOOFS_SUPERBLOCK_BLOCK_NUMBER = 0;
const int ASSOOFS_INODESTORE_BLOCK_NUMBER = 1;
const int ASSOOFS_ROOTDIR_DATABLOCK_NUMBER = 2;
const int ASSOOFS_ROOTDIR_INODE_NUMBER = 1;
const int ASSOOFS_MAX_FILESYSTEM_OBJECTS_SUPPORTED = 64; //MAX 64 bloques

struct assoofs_super_block_info { //Superbloque: info general del sistema de ficheros
    uint64_t version;
    uint64_t magic; //Número mágico
    uint64_t block_size; //Tamaño de bloque, 496    
    uint64_t inodes_count; //Número de inodos
    uint64_t free_blocks; //Bloques libres (1 libre, 0 ocupado)
    char padding[4056]; //Relleno, no se usa
};

struct assoofs_dir_record_entry { //Para directorios, lista del contenido 
    char filename[ASSOOFS_FILENAME_MAXLEN]; //Nombre del fichero
    uint64_t inode_no; //Número de inodo
};

struct assoofs_inode_info { //Info de MIS inodos
    mode_t mode; //Permisos
    uint64_t inode_no; //Número de inodo
    uint64_t data_block_number; //Bloque donde está almacenado el fichero
    union {
        uint64_t file_size; //Si es fichero, cuanto ocupa
        uint64_t dir_children_count; //Si es directorio, cuántos ficheros tiene dentro
    };
};

//Bloque 0: Info SuperBlock
//Bloque 1: Almacén inodos
//Bloque 2: Directorio raíz
//Bloque 3: README.txt
