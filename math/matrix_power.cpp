/**
 * 矩阵快速幂
 **/ 
typedef long long LL;
typedef vector<vector<LL> > Mat;
void Print(Mat mat) {
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[0].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
Mat Clear(Mat mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            mat[i][j] = 0;
        }
    }
    return mat;
}

Mat Init(Mat mat) {
    Clear(mat);
    for (int i = 0; i < mat.size(); i++) {
        mat[i][i] = 1;
    }
    return mat;
}

Mat Multiply(Mat mat1, Mat mat2, LL MOD) {
    Mat mat(mat1.size(), vector<LL>(mat2[0].size()));
    Clear(mat);
    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            for (int k = 0; k < mat1[0].size(); k++) {
                mat[i][j] = (mat[i][j] + (mat1[i][k] % MOD) * (mat2[k][j] % MOD)) % MOD;
            }
        }
    }
    return mat;
}

Mat MatQuickPow(Mat a, LL b, LL MOD) {
    Mat res(a.size(), vector<LL>(a[0].size()));
    res = Init(res);
    while (b) {
        if (b & 1)res = Multiply(res, a, MOD);
        a = Multiply(a, a, MOD);
        b >>= 1;
    }
    return res;
}