enum class RfTxtWeight { THIN, EXTRA_LIGHT, LIGHT, NORMAL, REGULAR, MEDIUM, BOLD, BLACK, HEAVY };
enum class RfTxtStyle { NORMAL, OBLIQUE, ITALIC };
enum class RfTxtStretch { CONDENSED, NORMAL, MEDIUM, EXPANDED, EXTRA_EXPANDED };
enum class RfTxtFlowDir { T_B, B_T, L_R, R_L };
enum class RfTxtParaAlign { ALIGN_NEAR, ALIGN_FAR, ALIGN_CENTER };
enum class RfTxtReadDir { L_R, R_L, T_B, B_T };
enum class RfTxtTextAlign { ALIGN_LEAD, ALIGN_TRAIL, ALIGN_CENTER, ALIGN_JUSTIFIED };
enum class RfTxtWordWrap { WRAP, NO_WRAP, EMERGENCY_BREAK, WHOLE_WORD, CHARACTER };
enum class RfTxtOverFlow{CLIP,NOT_CLIP};
namespace RfTXTFamilyName
{
	static const wchar_t* Gabriola = L"Gabriola";
	static const wchar_t* Arial = L"Arial";

};

struct RfTextStyle
{
	float size = 14.0f;
	const wchar_t* familyName = RfTXTFamilyName::Arial;
	const wchar_t* localFontName = L"en-us";
	RfTxtTextAlign align = RfTxtTextAlign::ALIGN_CENTER;
	RfTxtWeight weight = RfTxtWeight::NORMAL;
	RfTxtStyle style = RfTxtStyle::NORMAL;
	RfTxtStretch stretch = RfTxtStretch::NORMAL;
	RfTxtWordWrap wordWrap = RfTxtWordWrap::NO_WRAP;
	RfTxtParaAlign paraAlign = RfTxtParaAlign::ALIGN_CENTER;
	RfTxtReadDir readDir = RfTxtReadDir::L_R;
	RfTxtFlowDir flowDir = RfTxtFlowDir::T_B;
	RfTxtOverFlow overflow = RfTxtOverFlow::CLIP;
	void* Native();
};