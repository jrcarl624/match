#include "main.hpp"


/*
void AstBase::parse(std::span<Token> tokens) {

	int depth = 0;  // Initialized depth

	for (const Token& token : tokens) {
		using enum Token_e;

		switch (token.GetType()) {
			case OpenCurlyBracket:
			case OpenRoundBracket:
			case OpenAngleBracket:
			case OpenSquareBracket: {

				}
				// Handle other cases if needed
			default: {
					break;
				}
		}
	}

	return *this;  // Return the current object or adjust based on your actual parsing logic
}
*/

template <AstParse T>
std::expected<std::span<Token>, AstError> AstNode<T>::parse(std::span<Token> tokens) {
	// Implement parsing logic for AstNode
	return std::unexpected(AstError::Unimplemented);

}

std::expected<std::span<Token>, AstError>  AstVariable::parse(std::span<Token> tokens) {


	// Implement parsing logic for AstVariable
	return std::unexpected(AstError::Unimplemented);

}

template<AstParse T, str::ConstStr sep>
std::expected<std::span<Token>, AstError> AstSeparated<T, sep>::parse(std::span<Token> tokens) {

	// Implement parsing logic for AstSeparated
	static std::string_view sep_str = sep::MakeView();
	return std::unexpected(AstError::Unimplemented);


}

template<AstParse T, str::ConstStr start, str::ConstStr end>
std::expected <std::span<Token>, AstError> AstDelimited<T, start, end>::parse(std::span<Token> tokens) {
	static std::string_view start_str = start::MakeView();
	static std::string_view end_str = end::MakeView();



	if (tokens[0].GetSubTokensAsStr() != start_str) return std::unexpected(AstError::ExpectedToken);


	tokens = tokens.subspan(1);


	while (true) {


		T t;

		auto exp = t.parse(tokens);

		if (exp) {

			this->m_children.PushBack(tokens);

			if (tokens.first().GetSubTokensAsStr() == sep)
				tokens = tokens.subspan(1);
			else break;

		} 
		else return exp;
	}
	// fn params can be empty
	/*if (this->m_children.IsEmpty()) {


	}*/
	if () {};

	if (tokens[0].GetSubTokensAsStr() != end_str) return std::nullopt;

	return std::unexpected(AstError::Unimplemented);



}

std::expected<std::span<Token>, AstError> AstLabel::parse(std::span<Token> tokens) {
	// Implement parsing logic for AstLabel
	return std::unexpected(AstError::Unimplemented);

}

std::expected<std::span<Token>, AstError> AstFunctionHeader::parse(std::span<Token> tokens) {
	// Implement parsing logic for AstFunctionHeader
	return std::unexpected(AstError::Unimplemented);

}


std::expected<std::span<Token>, AstError> AstType::parse(std::span<Token> tokens) {
	return std::unexpected(AstError::Unimplemented);
};





int main() {

	std::vector<std::string> testSymbols{
		"public: virtual bool ServerNetworkHandler::allowIncomingPacketId(class NetworkIdentifier const &, enum MinecraftPacketIds)",
		"public: class OwnerPtr<class EntityContext> ServerNetworkHandler::createNewPlayer(class NetworkIdentifier const &, class ConnectionRequest const &)",
		"public: static std::function<int(thing)> Class<thing>::OtherThing() const",
		"public: std::function<int(thing)> functionName2()",
		"public: static int (*sa_sigaction)(int, siginfo_t *, void *)",
		"std::shared_ptr<RakNet::RakNetSocket2>::_Setpd<RakNet::RakNetSocket2 *,void (__cdecl*)(RakNet::RakNetSocket2 *)>'::`1'::dtor$",
		"`std::vector<entt::internal::dense_map_node<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::shared_ptr<br::worldgen::Structure> >,std::allocator<entt::internal::dense_map_node<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::shared_ptr<br::worldgen::Structure> > > >::_Emplace_reallocate<unsigned __int64 &,std::piecewise_construct_t const &,std::tuple<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &>,std::tuple<> >'::`1'::catch$5",
		"std::unordered_map<std::string, ItemUseMethod>::~unordered_map[abi::v15007]()",
		"BuriedTreasureFeature::getNearestGeneratedFeature(Dimension&, BiomeSource&, BlockPos const&, BlockPos&)",
	};

	// construct the lexer 
	Lexer tokenizer;

	for (std::string s : testSymbols) {
		SlideView<u8> source = SlideView<u8>(s);
		std::vector<Token> tokens = tokenizer.Lex(source);

		std::span<Token> slice{ tokens };

		// constructs a new ast node 
		AstFunctionHeader node;

		node.parse(slice);
	}







	return 0;
}

