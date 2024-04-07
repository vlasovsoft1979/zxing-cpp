#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ReadBarcode.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct Param
{
	const std::string ext;
	const std::string file;
	std::vector<std::string> expected;
};

std::ostream& operator << (std::ostream& o, const Param& param)
{
    o << param.file;
	return o;
}

class QrTestFixture :public ::testing::TestWithParam<Param> 
{
};

const std::vector<Param> test_params = {
	{ "png", "short_url1", {"https://qrco.de/a1b2c3"} },
	{ "png", "short_url1_rot", {"https://qrco.de/a1b2c3"} },
	{ "png", "short_url2", {"https://qrco.de/a1b2c3"} },
	{ "png", "short_url2_low", {"https://qrco.de/a1b2c3"} },
	{ "png", "short_url3", {"https://qrco.de/a1b2c3d5"} },
	{ "png", "short_url4", {"https://qrco.de/a1b2c3d5"} },
	{ "png", "short_url5", {"https://qrco.de/short5"} },
	{ "png", "short_url5_blu", {"https://qrco.de/short5"} },
	{ "png", "short_url6", {"https://qrco.de/short6"} },
	{ "png", "short_url6_per", {"https://qrco.de/short6"} },
	{ "png", "short_url7", {"https://qrco.de/short7"} },
	{ "png", "short_url7_rot_per", {"https://qrco.de/short7"} },
	{ "png", "short_url8", {"http://l.ead.me/short8"} },
	{ "png", "short_url9", {"http://l.ead.me/short9"} },
	{ "png", "short_url10", {"http://q-r.to/short10"} },
	{ "png", "long_url1", {"https://At-lease.comcheck.cloud/BEPZ1RU9T8L7IS4/dGZhaG15QGF0LWxlYXNlLmNvbQ==/PK2D9R4L96C6IZE"} },
	{ "png", "long_url2", {"https://gem.godaddy.com/signups/activate/MS0tQmIwM0E4YWFJcGtvdVVuNktlOHZydloxb2Z1WVhRWG5YeXdBZ3dTS3pabGQzcGdqMjJFTmg1UTRmSjZiMDdFbi9zV2oydFFlblYvRS0tbzQ0N1BoV2tSZEl5U0ZxZC0tOGlWNHZXYnVEN2xGV3l2QzF3emlKQT09?signup=6871485#am9zZWx1aXNAZmluaS5lcw=="} },
	{ "jpg", "long_url3", {"https://Eurochemgroup.carter-hay.com/7JXKQ7K08LYLR9RSNPLN/victoria.conwell@eurochemgroup.com"} },
	{ "png", "long_url4", {"https://Eurochemgroup.carter-hay.com/7JXKQ7K08LYLR9RSNPLN/victoria.conwell@eurochemgroup.com"} },
	{ "png", "long_url5", {"https://www.gliceriunsseguros.com.br/ituran/#YWNjb3VudHNAc3Vla2FnLmNvbQ==" } },
	{ "png", "long_url6", {"https://c8afw434.caspio.com/dp/f075c000559e22e4a6c144459d7c"} },
	{ "png", "long_url7", {"http://api.egorealestate.com/egocore/LandingPage/MarkCommunicationClick?token=dZZYEz5GCaMHpWgTdOeJzMy8+DGgX4M+JIc7JqVLdFaurIBm1XDeHQcYuuwJjCLQ&businessObjectID=1&metabaseID=17655618&redirect=https://Tajholding.i6x.net//T685CCMXDE3UIE5/ci5hbGlAdGFqaG9sZGluZy5jb20=/SV8X5PBMXZ"} },
	{ "png", "long_url8", {"http://api.egorealestate.com/egocore/LandingPage/MarkCommunicationClick?token=dZZYEz5GCaMHpWgTdOeJzMy8+DGgX4M+JIc7JqVLdFaurIBm1XDeHQcYuuwJjCLQ&businessObjectID=1&metabaseID=17655618&redirect=https://Netcracker.i6x.net/U9RZO6UX0SF9KFQ/vashistha.diwan@netcracker.com/NNTNFZ6PBOQDHQV"} },
	{ "png", "long_url9", {"http://api.egorealestate.com/egocore/LandingPage/MarkCommunicationClick?token=dZZYEz5GCaMHpWgTdOeJzMy8+DGgX4M+JIc7JqVLdFaurIBm1XDeHQcYuuwJjCLQ&businessObjectID=1&metabaseID=17655618&redirect=https://Tajholding.i6x.net//XMFHZUZSBTYAQ98/b3NhbWFAdGFqaG9sZGluZy5jb20=/97WUWV9VAR"} },
	{ "png", "long_url10", {"https://Eurochemgroup.carter-hay.com/7JXKQ7K08LYLR9RSNPLN/victoria.conwell@eurochemgroup.com"} },
	{ "png", "long_url11", {"https://Gazprom-media.bobwerks.com/Gazprom-media/a.zharov@gazprom-media.com/Gazprom-media"} },
	{ "png", "long_url12", {"https://surewayconsultants.com/_wildcard_.surewayconsultants.com/index.php/?dmFzaGlzdGhhLmRpd2FuQG5ldGNyYWNrZXIuY29t"} },
	{ "png", "long_url13", {"https://ipfs.io/ipfs/bafybeidzmwomb2seahiftouptmy37bty6g4zlmejj77pmgab7trxwq73fu/btmessageportalauytfghjdfyfop.html?cfg=YW5kcmVhLmxpc2lAZG9uZHVwLmNvbQ=="} },
	{ "jpg", "long_url14", {"https://lawsonlundeil.com/"} },
	{ "png", "long_url15", {"https://ipfs.io/ipfs/bafybeibe6vtqpu5xoxgqk5rqldawyzxdbdzo2owzpichc7q2zileuajgue/takeself.html#YW5CbGNtVjZRR05wWldGMWRHOXRiM1JwZG1VdVkyOXQ="} },
	{ "png", "long_url16", {"https://email.pednen5zbt2co0cv.asia"} },
	{ "png", "long_url17", {"https://e3qt2eyto3.adsmalonse.store/?email=infrasales@offimac.com"} },
	{ "gif", "long_url18", {"https://tehranrenter.com//alkaliness/evasss/lasenasss//amF2aWVyLnBhbGFjaW9zQHZhaWxsYW50LWdyb3VwLmNvbQ=="} },
	{ "png", "long_url19", {"https://is.gd/fy8fvg#em9sb3RhcmV2YV9lbUByZnMucnU="} },
	{ "png", "long_url20", {"https://cloudflare-ipfs.com/ipfs/bafybeiakz53et5bxx53r2dniv6ph6mj7f7hmg2uqsfyblerulfj3nqrvei/takeselfspark.html#YVhObGJtZDFjSFJoUUdKcGNteGhZMjl5Y0M1amIyMD0="} },
	{ "png", "long_url21", {"https://www.bing.com/ck/a?!&&p=7172f9757bc6ced9JmltdHM9MTY5NTI1NDQwMCZpZ3VpZD0yNDFiNDcyNC0xZjAwLTZlYTYtMTJiZS01NDBhMWViZTZmMWYmaW5zaWQ9NTE0Mw&ptn=3&hsh=3&fclid=241b4724-1f00-6ea6-12be-540a1ebe6f1f&u=a1aHR0cHM6Ly9tZWQtcGFyYWRpc2Uub3JnL2luZGV4LnBocC8yMDIyLzA3LzEzL2hva2lkZXdhdGEtbWFzdWsta2UtNi1wcm92aWRlci1wZXJtYWluYW4tdGVycGlsaWgtZGktMjAyMS1sYW50YXJhbi1wdW55YWktYmVyYWdhbS10eXBlLWdhbWUtc2xvdHMv#M=csmanagement@pureedgelighting.com"} },
	{ "png", "long_url22", {"https://documentsexchange-1321063488.cos.ap-nanjing.myqcloud.com/preview.html#marcos.rodellar@inycom.es"} },
	{ "gif", "long_url23", {"https://d.hodes.com/r/tp2?e=se&tv=pixel_tracker&p=web&aid=humanacrm&se_ca=email_unsub&se_ac=unsubscribe&se_la=12171&se_pr=5006&se_va=1923131&tr_id=&tr_af=9402&u=http://rand5.ianmatteson.com/#dgomez@lightology.com"} },
	{ "png", "long_url24", {"https://cn.bing.com/ck/a?!&&p=7e9ab7a60ffab264JmltdHM9MTY5MzE4MDgwMCZpZ3VpZD0wY2QyNDY4Mi00Mzg3LTZmZjctMWM3MC01NWE5NDI1YzZlNTQmaW5zaWQ9NTAwMw&ptn=3&hsh=3&fclid=0cd24682-4387-6ff7-1c70-55a9425c6e54&u=a1aHR0cHM6Ly9teWlwcy5jYy8#&&yygpKSi20tfPyy9JLimoqCq3rDTIzs3NMco2M9bLTSstziuq0Csq1c/JzcsvKNQHAA==?cy5ibGl6bnl1a0B0aW5rb2ZmLnJ1"} },
	{ "png", "long_url25", {"https://gem.godaddy.com/signups/activate/MS0tNjM4Qi9ua2NOWDRRdDdjeGhlT0poajhPcUR2Y2cxd2g3aFBuSXhGSmF6Nkd2dG54Tzdob1QwMm03OUhIdEtiOS9jN01RQlZqYVV1Y1Iyc3Q5dz09LS0wTjJWUDdQZUVPMFlYNXZQLS0yVy9aTEtFNkVReEYzVzYyRS9oZnR3PT0=?signup=6907687#ZXVnZW5lLmthc3BlcnNreUBrYXNwZXJza3kuY29t"} },
	{ "png", "long_url26", {"https://walterinsuranceonline.com/publicist"} },
	{ "jpg", "long_url27", {"https://cloudflare-ipfs.com/ipfs/bafybeihdebxuo5adudnzi4fgpfwsencm7wv5tauqomaslqn5nzlynlhnie/zoomeme.html#YjNCbGNtRjBhVzl1Y3pGQWJXVjBjbTlzYjJkcGMzUnBZM05yWlc1NVlTNWpiMjA9"} },
	{ "jpg", "long_url28", {"http://fashionbiz.co.kr/redirect.asp?url=https://secure.artnoblesexpressions.com/aweKMAHM"} },
	{ "gif", "long_url29", {"https://tehranrenter.com//alkaliness/evasss/lasenasss//amF2aWVyLnBhbGFjaW9zQHZhaWxsYW50LWdyb3VwLmNvbQ=="} },
	{ "png", "long_url30", {"https://cn.bing.com/ck/a?!&&p=7e9ab7a60ffab264JmltdHM9MTY5MzE4MDgwMCZpZ3VpZD0wY2QyNDY4Mi00Mzg3LTZmZjctMWM3MC01NWE5NDI1YzZlNTQmaW5zaWQ9NTAwMw&ptn=3&hsh=3&fclid=0cd24682-4387-6ff7-1c70-55a9425c6e54&u=a1aHR0cHM6Ly9teWlwcy5jYy8#&&yygpKSi20tfPyy9JLimoqCq3rDTIzs3NMco2M9bLTSstziuq0Csq1c/JzcsvKNQHAA==?cC50b2thcmV2QHRpbmtvZmYucnU="} },
	{ "png", "long_url31", {"https://is.gd/fy8fvg#Y2hlcmVzaG5ldmFfc3NAcmZzLnJ1"} },
	{ "png", "long_url32", {"https://companylawinfo.com/Mosama@tajholding.com"} },
	{ "png", "long_url33", {"https://3vcco45vbz7mk5g4ujpl.5nvu73x.ru/ejho/#patricia.bobaly@waberers.com"} },
	{ "png", "long_url34", {"https://cn.bing.com/ck/a?!&&p=7e9ab7a60ffab264JmltdHM9MTY5MzE4MDgwMCZpZ3VpZD0wY2QyNDY4Mi00Mzg3LTZmZjctMWM3MC01NWE5NDI1YzZlNTQmaW5zaWQ9NTAwMw&ptn=3&hsh=3&fclid=0cd24682-4387-6ff7-1c70-55a9425c6e54&u=a1aHR0cHM6Ly9teWlwcy5jYy8#&&yygpKSi20tfPyy9JLimoqCq3rDTIzs3NMco2M9bLTSstziuq0Csq1c/JzcsvKNQHAA==?di50c3lnYW5vdkB0aW5rb2ZmLnJ1"} },
	{ "png", "long_url35", {"=https://DOCUX.tntsupermarket.online/vashistha.diwan@netcracker.com"} },
	{ "png", "long_url36", {"https://8270132b.notifications-1c0.workers.dev?qrc=bWFyY29zLnJvZGVsbGFyQGlueWNvbS5lcw=="} },
	{ "png", "multi_url1", {"https://companylawinfo.com/Mosama@tajholding.com", "https://Eurochemgroup.carter-hay.com/7JXKQ7K08LYLR9RSNPLN/victoria.conwell@eurochemgroup.com"} },
};

INSTANTIATE_TEST_CASE_P(Main, QrTestFixture, ::testing::ValuesIn(test_params), ::testing::PrintToStringParamName());

TEST_P(QrTestFixture, Recognize)
{
	const Param& param = GetParam();
	auto file_name = "images/" + param.file + "." + param.ext; 
    int width = 0, height = 0, channels = 0;
    std::unique_ptr<stbi_uc, void(*)(void*)> buffer(stbi_load(file_name.c_str(), &width, &height, &channels, 1), stbi_image_free);
	ASSERT_TRUE(buffer != nullptr);
	ZXing::ImageView image{ buffer.get(), width, height, ZXing::ImageFormat::Lum };
	auto hints = ZXing::DecodeHints().setFormats(ZXing::BarcodeFormat::QRCode);
	auto data = ZXing::ReadBarcodes(image, hints);
	std::vector<std::string> result;
	for (const auto& v : data)
	{
		if (v.isValid())
		{
			result.push_back(v.text(ZXing::TextMode::Escaped));
		}
	}
	ASSERT_EQ(param.expected, result);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
