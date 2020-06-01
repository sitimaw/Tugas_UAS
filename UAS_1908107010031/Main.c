#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct data_peserta{
	char nik[17];
	char nama[21];
	char jk;
	char alamat[21];
	int hafalan;
	int target;
}data;
static const data EmptyStruct; //digunakan ketika menghapus data

void set(data * p, char * nik, char * nama, char jk, char * alamat, int haf, int tar);
void save(int j, data peserta[]);
void show(int j, data peserta[]);
void find(int a, data peserta[]);
void del(int a, int j, data peserta[]);

int main(){
	data peserta[100];
	data * pp;
	FILE * fp;
	unsigned long long len;
	
	int j=0; //variabel untuk menghitung jumlah data, akan increment setiap penambahan data dan decrement setiap penghapusan data

	fp = fopen("data/data.txt", "r"); //membuka file data.txt
	if(fp != NULL){
		fseek(fp, 0, SEEK_END);
		len = (unsigned long long)ftell(fp); //menghitung panjang file data.txt
	}
	if(fp == NULL || len == 0){ //jika file data.txt tidak ada atau kosong, maka data akan dibuat terlebih dahulu
		fclose(fp);
		//fungsi set untuk menyimpan data ke dalam struct, fungsi save untuk menyimpan data dari struct ke dalam file
		pp = &peserta[j];
		set(pp, "1172383001020003", "Sulthan", 'L', "Banda Aceh", 10, 30);
		++j;
		pp = &peserta[j];
		set(pp, "1073025003020002", "Siti Choirunnisa", 'P', "Padang", 10, 20);
		++j;
		pp = &peserta[j];
		set(pp, "1170041111010005", "Ahmad Bayu Zahirsyah", 'L', "Aceh Tamiang", 10, 30);
		++j;
		pp = &peserta[j];
		set(pp, "1174221011010003", "Muhammad Basri", 'L', "Nagan Raya", 3, 10);
		++j;
		pp = &peserta[j];
		set(pp, "1173010101010001", "Sri Yufita", 'P', "Sabang", 7, 15);
		++j;
		save(j, peserta);
	}else{ //jika data sudah ada, maka data diambil dari file data.txt dan menyimpannya ke memori(struct)
		fseek(fp, 0, SEEK_SET);
		char baris[100];
		char * sp;
		fgets(baris, sizeof(baris), fp);
		//data dipisahkan berdasarkan karakter koma(,) dengan fungsi strtok
		for(int i=0; ftell(fp) != len; ++i){
			fgets(baris, sizeof(baris), fp);
			sp = strtok(baris, ";");
			strcpy(peserta[i].nik, sp);
			sp = strtok(NULL, ";");
			strcpy(peserta[i].nama, sp);
			sp = strtok(NULL, ";");
			peserta[i].jk = *sp;
			sp = strtok(NULL, ";");
			strcpy(peserta[i].alamat, sp);
			sp = strtok(NULL, ";");
			peserta[i].hafalan = atoi(sp); //fungsi atoi untuk mengubah string menjadi integer
			sp = strtok(NULL, ";");
			peserta[i].target = atoi(sp);
			++j; //setiap ada proses penyimpanan data ke struct maka incremet j untuk menghitung jumlah data yang ada
		}
		fclose(fp);
	}

	printf("\n==================== SELAMAT DATANG =====================\n");
	printf("======== DI PORTAL DATA PESERTA PROGRAM TAHFIDZH ========\n");

	/* Proses Login */
	printf("\nLOGIN:");
	char username[21], password[21], u[21], p[21];

	fp = fopen("data/login.bin", "rb");
	if(fp != NULL){
		fseek(fp, 0, SEEK_END);
		len = (unsigned long long)ftell(fp);
	}
	//jika file login.bin belum ada atau kosong, maka data login dibuat terlebih dahulu
	if(fp == NULL || len == 0 || len == 2){ //jika nilai len adalah 0 atau 2 artinya file bin masih kosong
		fclose(fp);
		fp = fopen("data/login.bin", "wb");
		fwrite("mawaddah", sizeof(char), 21, fp);
		fwrite("mawmaw", sizeof(char), 21, fp);
		fclose(fp);
	}
//membaca data dari file login.bin
	fp = fopen("data/login.bin", "rb");
	fread(username, sizeof(char), 21, fp);
	fread(password, sizeof(char), 21, fp);
//proses autentikasi login
	do{
		printf("\nUsername: "); scanf(" %[^\n]", u);
		printf("Password: "); scanf(" %[^\n]", p);
		printf("Status  : ");
		if(strcmp(username,u) == 0 && strcmp(password,p) == 0){
			printf("Login berhasil\n");
			break;
		}else{
			printf("Username atau Password salah\n");
		}
	}while(1);

	fclose(fp);

	printf("\n================= SELAMAT DATANG ADMIN ==================\n");
	int pilihan;
	char cari[17];
	char nik[17], nama[21], jk, alamat[21];
	int haf, tar;
	char ubah, hapus;
	int admin;
	do{
		printf("\nMENU:\n1. Tampilkan Data Peserta\n2. Cari Data Peserta\n3. Tambah Data Peserta\n4. Hapus Data Peserta\n5. Ubah Data Peserta\n6. Pengaturan\n7. Keluar\n");
		printf("\nPilihan : "); scanf(" %d", &pilihan);
		switch (pilihan){
			case 1: //menampilkan data
			printf("\nDATA PESERTA\n");
			show(j, peserta);
			break;

			case 2: //mencari data
			printf("\nCARI DATA PESERTA\n");
			printf("NIK : "); scanf(" %[^\n]", cari);
			for(int a=0; a<=j+1; ++a){
				if(strcmp(peserta[a].nik, cari) == 0){
					find(a, peserta);
					break;
				}else if(a == j){
					printf("Data tidak dapat ditemukan\n");
					break;
				}
			}
			break;

			case 3: //menambah data
			printf("\nTAMBAH DATA PESERTA\n");
			while(1){
				printf("%-14s: ","NIK"); scanf(" %[^\n]", nik);
				if(strlen(nik) != 16)
					printf("\nNIK yang Anda masukkan tidak valid\n");
				else
					break;
			}
			printf("%-14s: ","Nama"); scanf(" %[^\n]", nama);
			while(1){
				printf("%-14s: ","Jenis Kelamin"); scanf(" %c", &jk);
				jk = toupper(jk);
				if(jk != 'P' && jk != 'L')
					printf("\nMohon masukkan 'P' atau 'L'\n");
				else
					break;
			}
			printf("%-14s: ","Alamat"); scanf(" %[^\n]", alamat);
			while(1){
				printf("%-14s: ","Jumlah hafalan"); scanf(" %d", &haf);
				if(haf < 0 || haf > 30)
					printf("\nMohon masukkan bilangan antara 0 - 30\n");
				else
					break;
			}
			while(1){
				printf("%-14s: ","Target hafalan"); scanf(" %d", &tar);
				if(tar < 1 || tar > 30)
					printf("\nMohon masukkan bilangan antara 1 - 30\n");
				else if(tar < haf)
					printf("\nMohon masukkan target yang lebih besar dari hafalan Anda\n");
				else
					break;
			}
			pp = &peserta[j];
			set(pp, nik, nama, jk, alamat, haf, tar); //menyimpan data tambahan ke struct
			++j; //jumlah data bertambah
			save(j, peserta); //mengupdate data di file
			printf("\n-> Data Berhasil Ditambah\n");
			show(j, peserta); //menampilkan data yang telah ditambah
			break;

			case 4: //menghapus data
			printf("\nHAPUS DATA PESERTA\n");
			printf("NIK : "); scanf(" %[^\n]", cari);
			for(int a=0; a<=j+1; ++a){
				if(strcmp(peserta[a].nik, cari) == 0){
					printf("Anda yakin ingin menghapus data atas nama '%s'? (y/n): ", peserta[a].nama); scanf(" %c", &hapus);
					hapus = tolower(hapus);
					if(hapus == 'y'){
						del(a, j, peserta); //menghapus data dari struct
						--j; //jumlah data berkurang
						save(j, peserta); //mengupdate data di file
						printf("\n-> Data Berhasil Dihapus\n");
						show(j, peserta); //menampilkan sisa data setelah dihapus
						break;
					}else{
						break;
					}
				}else if(a == j){
					printf("Data tidak dapat ditemukan\n");
					break;
				}
			}
			break;

			case 5: //mengubah data
			printf("\nUBAH DATA PESERTA\n");
			printf("NIK : "); scanf(" %[^\n]", cari);
			for(int a=0; a<=j+1; ++a){
				if(strcmp(peserta[a].nik, cari) == 0){
					printf("Ubah NIK (y/n): "); scanf(" %c", &ubah);
					ubah = tolower(ubah);
					if(ubah == 'y'){
						while(1){
							printf("%-14s: ","NIK"); scanf(" %[^\n]", nik);
							if(strlen(nik) != 16)
								printf("\nNIK yang Anda masukkan tidak valid\n");
							else
								break;
						}
					}else{
						strcpy(nik, peserta[a].nik);
					}
					printf("Ubah nama (y/n): "); scanf(" %c", &ubah);
					if(ubah == 'y'){
						printf("%-14s: ","Nama"); scanf(" %[^\n]", nama);
					}else{
						strcpy(nama, peserta[a].nama);
					}
					printf("Ubah jenis kelamin (y/n): "); scanf(" %c", &ubah);
					if(ubah == 'y'){
						while(1){
							printf("%-14s: ","Jenis Kelamin"); scanf(" %c", &jk);
							jk = toupper(jk);
							if(jk != 'P' && jk != 'L')
								printf("\nMohon masukkan 'P' atau 'L'\n");
							else
								break;
						}
					}else{
						jk = peserta[a].jk;
					}
					printf("Ubah alamat (y/n): "); scanf(" %c", &ubah);
					if(ubah == 'y'){
						printf("%-14s: ","Alamat"); scanf(" %[^\n]", alamat);
					}else{
						strcpy(alamat, peserta[a].alamat);
					}
					printf("Ubah jumlah hafalan (y/n): "); scanf(" %c", &ubah);
					if(ubah == 'y'){
						while(1){
							printf("%-14s: ","Jumlah hafalan"); scanf(" %d", &haf);
							if(haf < 0 || haf > 30)
								printf("\nMohon masukkan bilangan antara 0 - 30\n");
							else
								break;
						}
					}else{
						haf = peserta[a].hafalan;
					}
					printf("Ubah target hafalan (y/n): "); scanf(" %c", &ubah);
					if(ubah == 'y'){
						while(1){
							printf("%-14s: ","Target hafalan"); scanf(" %d", &tar);
							if(tar < 1 || tar > 30)
								printf("\nMohon masukkan bilangan antara 1 - 30\n");
							else if(tar < haf)
								printf("\nMohon masukkan target yang lebih besar dari hafalan Anda\n");
							else
								break;
						}
					}else{
						tar = peserta[a].target;
					}
					pp = &peserta[a];
					set(pp, nik, nama, jk, alamat, haf, tar); //menyimpan data ke struct
					save(j, peserta); //menyimpan data ke file
					printf("\n-> Data Berhasil Diubah\n");
					show(j, peserta);
					break;
				}else if(a == j){
					printf("Data tidak dapat ditemukan\n");
					break;
				}
			}
			break;

			case 6: //ubah username atau ubah password
			fp = fopen("data/login.bin", "rb");
			fread(username, sizeof(char), 21, fp);
			fread(password, sizeof(char), 21, fp);
			fclose(fp);
			
			do{
			printf("\nPENGATURAN ADMIN\n");
			printf("1. Ganti Username\n2. Ganti Password\n3. Kembali\n");
			printf("Pilihan: "); scanf(" %d", &admin);
			if(admin == 1){
				while(1){
					char cek[21]; //array cek digunakan untuk memeriksa panjang karakter yang dimasukkan
					printf("\nMasukkan username baru : "); scanf(" %s",cek);
					if(strlen(cek) < 21){
						strcpy(u, cek);
						break;
					}
					else{
						printf("Maksimal panjang username 20 karakter!\n");
					}
				}
				fp = fopen("data/login.bin", "wb");
				fwrite(u, sizeof(char), 21, fp);
				fwrite(password, sizeof(char), 21, fp);
				fclose(fp);
				strcpy(username, u);
				printf("\n->Username berhasil diganti\n");
			}else if(admin == 2){
				for(int z=0; z<3; ++z){
					printf("\nMasukkan password saat ini : "); scanf(" %s",p);
					if(strcmp(password,p) == 0){
						while(1){
							char cek[21];
							printf("\nMasukkan password baru : "); scanf(" %s",cek);
							if(strlen(cek) < 21){
								strcpy(p, cek);
								break;
							}
							else
								printf("Maksimal panjang password 20 karakter!\n");
						}
						fp = fopen("data/login.bin", "wb");
						fwrite(username, sizeof(char), 21, fp);
						fwrite(p, sizeof(char), 21, fp);
						fclose(fp);
						strcpy(password, p);
						printf("\n->Password berhasil diganti\n");
						break;
					}else{
						printf("Password salah\n");
						if(z == 2){ //jika terjadi 3 kali kesalahan dalam memasukkan password maka user diminta coba di lain waktu
							printf("\n->Coba lagi di lain waktu\n");
							break;
						}
					}
				}
			}else if(admin == 3){ //tidak ada statement apapun dan kembali ke menu
			}else{
				printf("Pilihan tidak tersedia\n");
			}
			}while(admin != 3);
			break;

			case 7:
			break;

			default:
			printf("Pilihan tidak tersedia\n");
			break;
		}
	}while(pilihan != 7);
	printf("\n================== PORTAL DATA DITUTUP ==================\n");

	return 0;
}
//fungsi set untuk menyimpan data ke dalam struct
void set(data * p, char * nik, char * nama, char jk, char * alamat, int haf, int tar){
	strcpy(p->nik, nik);
	strcpy(p->nama, nama);
	p->jk = jk;
	strcpy(p->alamat, alamat);
	p->hafalan = haf;
	p->target = tar;
}
//fungsi save untuk menyimpan data dari struct ke dalam file data.txt
void save(int j, data peserta[]){
	FILE * fp = fopen("data/data.txt", "w");
	fprintf(fp,"nik;nama;jk;alamat;hafalan;target\n");
	for(int i=0; i<j; ++i){
		fprintf(fp,"%s;%s;%c;%s;%d;%d\n",peserta[i].nik, peserta[i].nama, peserta[i].jk, peserta[i].alamat, peserta[i].hafalan, peserta[i].target);
	}
	fclose(fp);
}
//fungsi show untuk menampilkan seluruh data peserta
void show(int j, data peserta[]){
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
	printf("| NO |       NIK        |         NAMA         | JK |        ALAMAT        | HAFALAN | TARGET |\n");
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
	for(int i=0; i<j; ++i){
		printf("| %-3d| %-17s| %-21s| %c  | %-21s|%5d    |%5d   |\n", i+1, peserta[i].nik, peserta[i].nama, peserta[i].jk, peserta[i].alamat, peserta[i].hafalan, peserta[i].target);
	}
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
}
//fungsi find untuk menampilkan data peserta yang dicari
void find(int a, data peserta[]){
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
	printf("| NO |       NIK        |         NAMA         | JK |        ALAMAT        | HAFALAN | TARGET |\n");
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
	printf("| %-3d| %-17s| %-21s| %c  | %-21s|%5d    |%5d   |\n", 1, peserta[a].nik, peserta[a].nama, peserta[a].jk, peserta[a].alamat, peserta[a].hafalan, peserta[a].target);
	printf("+----+------------------+----------------------+----+----------------------+---------+--------+\n");
}
//fungsi delete untuk menghapus data peserta
void del(int a, int j, data peserta[]){
	for(; a<j; ++a){
		peserta[a] = peserta[a+1];
	}
	peserta[a] = EmptyStruct;
}