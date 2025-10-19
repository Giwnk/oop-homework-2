# File: meson.build

# ---- 1. Definisi Proyek ----
project('oop-homework-2', 'cpp',
    version: '1.0.0',
    default_options: [
        'cpp_std=c++20',
        'warning_level=3',
        'werror=true',       # Anggap semua warning sebagai error, biar kode makin berkualitas!
        'optimization=s'     # Optimasi ukuran file .exe
    ]
)

# ---- 2. Argumen Tambahan untuk Compiler ----
# Ini setelan "mode sulit" yang bikin kodemu makin solid. Keep it.
cpp_args = [
    '-Wpedantic',
    '-Wformat=2',
    '-Wundef',
    '-Wcast-align',
    '-Wwrite-strings',
    '-Wold-style-cast',
    '-Wnull-dereference',
    '-Wctor-dtor-privacy',
    '-Wno-missing-field-initializers',
]
add_global_arguments(cpp_args, language : 'cpp')

# ---- 3. Daftar Semua File Source (.cpp) ----
# Kita daftarkan semua "bahan baku" .cpp di sini. Perhatikan path-nya!
app_sources = [
    'main.cpp',
    'Database.cpp',
    'Handlers/handlers.cpp',
    'Services/Bank.cpp',
    'Services/BankCustomer.cpp',
    'Services/BankTransaction.cpp',
    'Services/Buyer.cpp',
    'Services/Item.cpp',
    'Services/Seller.cpp',
    'Services/Store.cpp',
    'Services/Transaction.cpp'

]



# ---- 4. Membuat File Executable ----
# Beritahu Meson untuk membuat 'main.exe' dari semua sumber utama
executable('main', app_sources,
    include_directories: ['.', 'Headers'],
    install: true
)
