/**
 * 任意模数fft
 * 用于求多项式卷积
 * 时间复杂度O(nlogn)
 **/ 
typedef long long ll;
typedef double DB;
const DB pi = acos(-1.0);
const ll maxn = 100005, maxLen = 18, maxm = 1LL << maxLen | 1;
struct Complex {
	DB r, i;
	Complex() {}
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
	Complex conj() const { return Complex(r, -i); }
} w[maxm];
int sp, msk;
void FFT_init(int mod) {
	for(int i = 0, iLim = 1 << maxLen; i < iLim; ++i) {
		int j = i, k = iLim >> 1; // 2 pi / iLim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = Complex(cos(pi / k * j), sin(pi / k * j));
	}
	for(sp = 1; 1 << (sp << 1) < mod; ++sp);
	msk = (1 << sp) - 1;
}
void FFT(int n, Complex a[], int flag) {
	static int bitLen = 0, bitRev[maxm] = {};
	if(n != (1 << bitLen)) {
		for(bitLen = 0; 1 << bitLen < n; ++bitLen);
		for(int i = 1; i < n; ++i)
			bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 0; i < n; ++i)
		if(i < bitRev[i])
			std::swap(a[i], a[bitRev[i]]);
	for(int i = 1, d = 1; d < n; ++i, d <<= 1)
		for(int j = 0; j < n; j += d << 1)
			for(int k = 0; k < d; ++k) {
				Complex &AL = a[j + k], &AH = a[j + k + d];
				Complex TP = w[k << (maxLen - i)] * AH;
				AH = AL - TP;
				AL = AL + TP;
			}
	if(flag != -1)
		return;
	std::reverse(a + 1, a + n);
	for(int i = 0; i < n; ++i) {
		a[i].r /= n;
		a[i].i /= n;
	}
}
void poly_conv(int aLen, int a[], int bLen, int b[], int cLen, int c[], int mod, bool flag = 0) { // len for array length
	int len;
	static Complex A[maxm], B[maxm], C[maxm], D[maxm];
	if(flag)
		for(len = 1; len < cLen; len <<= 1);
	else
		for(len = 1; len < aLen + bLen - 1; len <<= 1);
	for(int i = 0; i < len; ++i) {
		A[i] = i < aLen ? Complex(a[i] & msk, a[i] >> sp) : Complex(0, 0);
		B[i] = i < bLen ? Complex(b[i] & msk, b[i] >> sp) : Complex(0, 0);
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
	for(int i = 0; i < len; ++i) {
		int j = (len - i) & (len - 1);
		Complex AL = (A[i] + A[j].conj()) * trL;
		Complex AH = (A[i] - A[j].conj()) * trH;
		Complex BL = (B[i] + B[j].conj()) * trL;
		Complex BH = (B[i] - B[j].conj()) * trH;
		C[i] = AL * (BL + BH * tr);
		D[i] = AH * (BL + BH * tr);
	}
	FFT(len, C, -1);
	FFT(len, D, -1);
	for(int i = 0; i < cLen; ++i) {
		int v11 = (ll)(C[i].r + 0.5) % mod, v12 = (ll)(C[i].i + 0.5) % mod;
		int v21 = (ll)(D[i].r + 0.5) % mod, v22 = (ll)(D[i].i + 0.5) % mod;
		c[i] = (((((ll)v22 << sp) + v12 + v21) << sp) + v11) % mod;
	}
}