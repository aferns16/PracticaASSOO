#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrea Fernández");

//if(assoofs_sb -> magic != ASSOOFS_MAGIC)
//sb->s_magic = assoofs_magic;
//sb-> s_maxbytes = 4096;
//sb-> s_op = assoofs_sops;
//sb->s_fs_info = assoofs_sb;



//FICHEROS

ssize_t assoofs_read ( struct file * filp , char __user * buf , size_t len , loff_t * ppos );
ssize_t assoofs_write ( struct file * filp , const char __user * buf , size_t len , loff_t * ppos );
const struct file_operations assoofs_file_operations = {
	.read = assoofs_read ,
	.write = assoofs_write ,
};



ssize_t assoofs_read ( struct file * filp , char __user * buf , size_t len , loff_t * ppos ) {
	printk ( KERN_INFO "Read request\n") ;
	return 0;//nbytes ;
}

ssize_t assoofs_write ( struct file * filp , const char __user * buf , size_t len , loff_t * ppos ) {
	printk ( KERN_INFO "Write request\n") ;
	return 0;//len ;
}


//DIRECTORIOS

static int assoofs_iterate ( struct file * filp , struct dir_context * ctx ) ;
const struct file_operations assoofs_dir_operations={
	.owner = THIS_MODULE,
	.iterate = assoofs_iterate,
};

static int assoofs_iterate ( struct file * filp , struct dir_context * ctx ) {
	printk ( KERN_INFO "Iterate request\n" ) ;
	return 0;
}

//INODOS

static int assoofs_create ( struct inode * dir , struct dentry * dentry , umode_t mode , bool excl ) ;
static int assoofs_mkdir ( struct inode * dir , struct dentry * dentry , umode_t mode ) ;
struct dentry * assoofs_lookup ( struct inode * parent_inode , struct dentry * child_dentry , unsigned int flags );
static struct inode_operations assoofs_inode_ops = {
	.create = assoofs_create,
	.lookup = assoofs_lookup,
	.mkdir = assoofs_mkdir,
};

struct dentry * assoofs_lookup ( struct inode * parent_inode , struct dentry * child_dentry , unsigned int flags ) {
	printk ( KERN_INFO " Lookup request \n " ) ;
	return NULL ;
}

static int assoofs_create ( struct inode * dir , struct dentry * dentry , umode_t mode , bool excl ) {
	printk ( KERN_INFO " New file request \n " ) ;
	return 0;
}

static int assoofs_mkdir ( struct inode * dir , struct dentry * dentry , umode_t mode ) {
	printk ( KERN_INFO " New directory request \n " ) ;
	return 0;
}


//SUPERBLOQUE


static const struct super_operations assoofs_sops = {
	.drop_inode = generic_delete_inode,
};

int assoofs_fill_super(struct super_block *sb, void * data, int silent){
// 1. - Leer la información persistente del superbloque del dispositivo de bloques

	//buffer_head bh = *sb_bread(super_block *sb ,sector_t block );
	

// 2. - Comprobar los parámetros del superbloque
// 3. - Escribir la información persistente leı́da del dispositivo de bloques en el superbloque sb , incluı́do el campos_op con las operaciones que soporta .
// 4. - Crear el inodo ra ı́ z y asignarle operaciones sobre inodos ( i_op ) y sobre directorios ( i_fop )

	return 0;
}

static struct dentry * assoofs_mount (struct file_system_type * fs_type , int flags , const char * dev_name , void * data)
{
	
	struct dentry * ret = mount_bdev (fs_type, flags, dev_name, data, assoofs_fill_super);
}

//getinodeinfo (superbloque, inodo que busco)

static struct file_system_type assoofs_type = {
	.owner= THIS_MODULE,
	.name= "assoofs",
	.mount= assoofs_mount,
	.kill_sb = kill_litter_super,
};

static int __init assoofs_init(void)
{
	printk(KERN_INFO "Starting...\n");
	int ret = register_filesystem (&assoofs_type);
		if(ret == 0)
			printk(KERN_INFO "Sistema registrado correctamente");
		else
			printk(KERN_INFO "Error en el registro del sistema");
	

}
static void __exit assoofs_exit(void)
{
	int ret = unregister_filesystem(&assoofs_type);
		if(ret == 0)
			printk(KERN_INFO "Sistema registrado correctamente");
		else
			printk(KERN_INFO "Error en el registro del sistema");
}


module_init(assoofs_init); //Cargar módulo en el kernel
module_exit(assoofs_exit); //Descargar módulo


