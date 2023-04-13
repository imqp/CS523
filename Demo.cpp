#include <bits/stdc++.h>

using namespace std;

// Định nghĩa cấu trúc một node
struct Node {
    int Sum, Max, Min;
    long long Product;

    // Khởi tạo node
    Node() {
        Sum = 0;
        Max = INT_MIN;
        Min = INT_MAX;
        Product = 1;
    }
};

// Hàm gộp 2 node
Node merge(Node& left, Node& right);

// Hàm tạo cây phân đoạn
void build(Node* SegmentTree, int* arr, int id, int low, int high);

// Hàm cập nhật phần tử thứ i
void update(Node* SegmentTree, int id, int low, int high, int i, int val);

// Hàm cập nhật đoạn [i,j]
void rangeUpdate(Node* SegmentTree, int id, int low, int high, int i, int j, int val);

// Hàm truy vấn đoạn [i,j]
Node query(Node* SegmentTree, int id, int low, int high, int i, int j);


int main() {
    int N;
    cout << "Nhap so phan tu cua mang: ";
    cin >> N;

    int arr[N];
    cout << "Nhap cac phan tu cua mang: ";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    Node SegmentTree[4 * N];

    build(SegmentTree, arr, 0, 0, N - 1);

    while (true) {
        cout << "Mang hien tai: ";
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "1. Cap nhat phan tu" << endl;
        cout << "2. Cap nhat doan" << endl;
        cout << "3. Tim tong" << endl;
        cout << "4. Tim tich" << endl;
        cout << "5. Tim max" << endl;
        cout << "6. Tim min" << endl;
        cout << "7. Thoat" << endl;

        cout << "Nhap lua chon: " << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            int i, val;
            cout << "Nhap vi tri can cap nhat: ";
            cin >> i;
            cout << "Nhap gia tri can cap nhat: ";
            cin >> val;

            arr[i] = val;
            update(SegmentTree, 0, 0, N - 1, i, val);
        }
        else if (choice == 2) {
            int i, j, val;
            cout << "Nhap doan can cap nhat:";
            cin >> i >> j;
            cout << "Nhap gia tri can cap nhat: ";
            cin >> val;

            rangeUpdate(SegmentTree, 0, 0, N - 1, i, j, val);
            for (i; i <= j; i++) {
                arr[i] = val;
            }
        }
        else if (choice == 3) {
            int i, j;
            cout << "Nhap doan can tinh tong: ";
            cin >> i >> j;

            cout << "Tong cua doan [" << i << ", " << j << "] la: ";
            cout << query(SegmentTree, 0, 0, N - 1, i, j).Sum << endl;
            cout << "==============================" << endl;
        }
        else if (choice == 4) {
            int i, j;
            cout << "Nhap doan can tinh tich: ";
            cin >> i >> j;

            cout << "Tich cua doan [" << i << ", " << j << "] la: ";
            cout << query(SegmentTree, 0, 0, N - 1, i, j).Product << endl;
            cout << "==============================" << endl;
        }
        else if (choice == 5) {
            int i, j;
            cout << "Nhap doan can tim max: ";
            cin >> i >> j;

            cout << "Max cua doan [" << i << ", " << j << "] la: ";
            cout << query(SegmentTree, 0, 0, N - 1, i, j).Max << endl;
            cout << "==============================" << endl;
        }
        else if (choice == 6) {
            int i, j;
            cout << "Nhap doan can tim min: ";
            cin >> i >> j;

            cout << "Min cua doan [" << i << ", " << j << "] la: ";
            cout << query(SegmentTree, 0, 0, N - 1, i, j).Min << endl;
            cout << "==============================" << endl;
        }
        else if (choice == 7) {
            break;
        }
    }
}


Node merge(Node& left, Node& right) {
    Node parent;

    parent.Sum = left.Sum + right.Sum;
    parent.Max = max(left.Max, right.Max);
    parent.Min = min(left.Min, right.Min);
    parent.Product = left.Product * right.Product;

    return parent;
}

void build(Node* SegmentTree, int* arr, int id, int low, int high) {
    // Trường hợp đoạn có 1 phần tử, node đang xét là node lá
    if (low == high) {
        SegmentTree[id].Sum = arr[low];
        SegmentTree[id].Max = arr[low];
        SegmentTree[id].Min = arr[low];
        SegmentTree[id].Product = arr[low];
        return;
    }

    // Trường hợp đoạn có nhiều hơn 1 phần tử
    int mid = (low + high) / 2;
    build(SegmentTree, arr, 2 * id + 1, low, mid);
    build(SegmentTree, arr, 2 * id + 2, mid + 1, high);

    SegmentTree[id] = merge(SegmentTree[2 * id + 1], SegmentTree[2 * id + 2]);
}

void update(Node* SegmentTree, int id, int low, int high, int i, int val) {
    // i nằm ngoài đoạn [low, high]
    if (low > i || high < i)
        return;

    // Trường hợp node lá (đoạn có 1 phần tử)
    if (low == high) {
        SegmentTree[id].Sum = SegmentTree[id].Product = val;
        SegmentTree[id].Max = SegmentTree[id].Min = val;
        return;
    }

    // Trường hợp không phải node lá
    int mid = (low + high) / 2;
    update(SegmentTree, 2 * id + 1, low, mid, i, val);
    update(SegmentTree, 2 * id + 2, mid + 1, high, i, val);

    SegmentTree[id] = merge(SegmentTree[2 * id + 1], SegmentTree[2 * id + 2]);
}

void rangeUpdate(Node* SegmentTree, int id, int low, int high, int i, int j, int val) {
    // Trường hợp không giao nhau
    if (low > j || high < i)
        return;

    // Các trường hợp giao nhau
    // Trường hợp là node lá
    if (low == high) {
        SegmentTree[id].Sum = SegmentTree[id].Product = val;
        SegmentTree[id].Max = SegmentTree[id].Min = val;
        return;
    }

    // Trường hợp không là node lá
    int mid = (low + high) / 2;
    rangeUpdate(SegmentTree, 2 * id + 1, low, mid, i, j, val);
    rangeUpdate(SegmentTree, 2 * id + 2, mid + 1, high, i, j, val);

    SegmentTree[id] = merge(SegmentTree[2 * id + 1], SegmentTree[2 * id + 2]);
}

Node query(Node* SegmentTree, int id, int low, int high, int i, int j) {
    // Trường hợp không giao nhau
    if (low > j || high < i) {
        Node nullNode;
        return nullNode;
    }

    // Trường hợp đoạn [low, high] nằm trong đoạn [i, j]
    if (low >= i && high <= j)
        return SegmentTree[id];

    // Trường hợp đoạn [low, high] giao với đoạn [i, j]
    int mid = (low + high) / 2;
    Node left = query(SegmentTree, 2 * id + 1, low, mid, i, j);
    Node right = query(SegmentTree, 2 * id + 2, mid + 1, high, i, j);

    return merge(left, right);
}
