#include <iostream>
#include <fstream> // Tambahkan library ini untuk operasi file
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAX_TRANSAKSI = 100;

string tanggalTransaksi[MAX_TRANSAKSI];
string kategoriTransaksi[MAX_TRANSAKSI];
double pengeluaran[MAX_TRANSAKSI];
double pemasukan[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

// Fungsi untuk membersihkan layar konsol
void clearScreen()
{
    system("cls");
    cout << string(0, '\n');
}

double total_pengeluaran_bulanan = 0; // Inisialisasi variabel total pengeluaran bulanan

void tambahTransaksi()
{
    system("cls");
    clearScreen();
    if (jumlahTransaksi >= MAX_TRANSAKSI)
    {
        cout << "Jumlah transaksi sudah mencapai batas maksimum.\n";
        return;
    }

    cout << "================= Transaksi =================" << endl;
    cout << "Masukkan Tanggal Transaksi (DD/MM/YYYY): ";
    cin >> tanggalTransaksi[jumlahTransaksi];

    cout << "Masukkan Kategori Transaksi (1. Makanan, 2. Transportasi, 3. DLL): ";
    int kategori;
    cin >> kategori;
    switch (kategori)
    {
    case 1:
        kategoriTransaksi[jumlahTransaksi] = "Makanan";
        break;
    case 2:
        kategoriTransaksi[jumlahTransaksi] = "Transportasi";
        break;
    case 3:
        kategoriTransaksi[jumlahTransaksi] = "DLL";
        break;
    default:
        cout << "Kategori tidak valid.\n";
        return;
    }

    cout << "Masukkan Jumlah Pengeluaran (kosongkan jika tidak ada): ";
    cin >> pengeluaran[jumlahTransaksi];

    cout << "Masukkan Jumlah Pemasukan (kosongkan jika tidak ada): ";
    cin >> pemasukan[jumlahTransaksi];

    // Menambahkan jumlah pengeluaran ke total pengeluaran bulanan
    total_pengeluaran_bulanan += pengeluaran[jumlahTransaksi];

    jumlahTransaksi++;
    cout << "Transaksi berhasil ditambahkan.\n";
}

void rekapLaporanBulanIni()
{
    system("cls");
    clearScreen();
    cout << "============= Laporan Transaksi Bulan Ini =============\n";
    // Mendapatkan tanggal hari ini
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int bulanIni = localTime->tm_mon + 1; // Bulan dimulai dari 0
    int hariIni = localTime->tm_mday;
    int tahunIni = localTime->tm_year + 1900; // Tahun dimulai dari 1900

    bool adaTransaksi = false;

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        int bulan, hari, tahun;
        sscanf(tanggalTransaksi[i].c_str(), "%*d/%d/%d", &bulan, &tahun);
        hari = atoi(tanggalTransaksi[i].substr(0, 2).c_str());

        if (bulan == bulanIni && tahun == tahunIni && hari == hariIni)
        {
            cout << "Tanggal Transaksi: " << tanggalTransaksi[i] << endl;
            cout << "Kategori Transaksi: " << kategoriTransaksi[i] << endl;
            cout << "Jumlah Pengeluaran: " << pengeluaran[i] << endl;
            cout << "Jumlah Pemasukan: " << pemasukan[i] << endl;
            cout << "---------------------------------------------\n";
            adaTransaksi = true;
        }
    }

    if (!adaTransaksi)
    {
        cout << "Tidak ada transaksi pada tanggal ini.\n";
    }

    cout << "Tekan tombol apapun untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void rekapLaporanSemua()
{
    system("cls");
    clearScreen();
    cout << "========== Laporan Semua Transaksi ==========\n";
    ofstream outputFile("laporan.txt"); // Membuka file untuk menulis

    outputFile << "========== Laporan Semua Transaksi ==========\n";

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        cout << "Tanggal Transaksi: " << tanggalTransaksi[i] << endl;
        cout << "Kategori Transaksi: " << kategoriTransaksi[i] << endl;
        cout << "Jumlah Pengeluaran: " << pengeluaran[i] << endl;
        cout << "Jumlah Pemasukan: " << pemasukan[i] << endl;
        cout << "---------------------------------------------\n";

        // Menulis data ke file
        outputFile << "Tanggal Transaksi: " << tanggalTransaksi[i] << endl;
        outputFile << "Kategori Transaksi: " << kategoriTransaksi[i] << endl;
        outputFile << "Jumlah Pengeluaran: " << pengeluaran[i] << endl;
        outputFile << "Jumlah Pemasukan: " << pemasukan[i] << endl;
        outputFile << "---------------------------------------------\n";
    }

    outputFile.close(); // Menutup file
    cout << "Data laporan telah disimpan ke dalam file 'laporan.txt'.\n";
    cout << "Tekan tombol apapun untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

int main()
{
    while (true)
    {
        system("cls");
        clearScreen();
        cout << "========= Aplikasi Money Management =========\n";
        cout << "1. Transaksi\n";
        cout << "2. Rekap Laporan Bulan Ini\n";
        cout << "3. Rekap Laporan Semua Transaksi\n";
        cout << "4. Keluar\n";
        cout << "=============================================\n";

        int pilihan;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahTransaksi();
            break;
        case 2:
            rekapLaporanBulanIni();
            break;
        case 3:
            rekapLaporanSemua();
            break;
        case 4:
            cout << "Terima kasih telah menggunakan aplikasi Money Management.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
    return 0;
}
